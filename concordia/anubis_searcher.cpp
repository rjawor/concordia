#include "concordia/anubis_searcher.hpp"

#include "concordia/common/logging.hpp"
#include <boost/foreach.hpp>
#include <iostream>

AnubisSearcher::AnubisSearcher() {
}


AnubisSearcher::~AnubisSearcher() {
}


boost::ptr_vector<AnubisSearchResult> AnubisSearcher::anubisSearch(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                boost::shared_ptr<std::vector<INDEX_CHARACTER_TYPE> > pattern)
                                                throw(ConcordiaException) {
    boost::shared_ptr<TmMatchesMap> tmMatchesMap = getTmMatches(T, markers, SA, pattern);
    
    // get the tmMatches list sorted descending by score
    boost::ptr_vector<AnubisSearchResult> result;
    return result;
}

boost::shared_ptr<TmMatchesMap> AnubisSearcher::getTmMatches(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                boost::shared_ptr<std::vector<INDEX_CHARACTER_TYPE> > pattern)
                                                throw(ConcordiaException) {

    boost::shared_ptr<std::vector<sauchar_t> > patternVector =
        Utils::indexVectorToSaucharVector(pattern);

    if (patternVector->size() !=
        pattern->size() * sizeof(INDEX_CHARACTER_TYPE)) {
        throw ConcordiaException("Increasing pattern resolution went wrong.");
    }

    boost::shared_ptr<TmMatchesMap> tmMatchesMap(new TmMatchesMap());
    for (int offset = 0; offset < pattern->size(); offset++) {
        int highResOffset = offset * sizeof(INDEX_CHARACTER_TYPE);
        boost::shared_ptr<std::vector<sauchar_t> > currentPattern =
            boost::shared_ptr<std::vector<sauchar_t> >
            (new std::vector<sauchar_t>(
            patternVector->begin()+highResOffset, patternVector->end()));
            
        saidx_t patternLength = 0;
        saidx_t size = SA->size();
        saidx_t left = 0;

        sauchar_t * patternArray = currentPattern->data();

        saidx_t * SAleft = SA->data();

        saidx_t prevLeft;
        saidx_t prevSize;
        do {
            prevLeft = left;
            prevSize = size;

            patternLength += sizeof(INDEX_CHARACTER_TYPE);

            saidx_t localLeft;
            size = sa_search(T->data(), (saidx_t) T->size(),
                                 (const sauchar_t *) patternArray, patternLength,
                                 SAleft, size, &localLeft);


            left += localLeft;
            SAleft += localLeft;

            if (patternLength > sizeof(INDEX_CHARACTER_TYPE)) {
                // Add to tm matches map results surrounding the main stream.
                // from left
                for (saidx_t i = prevLeft; i < left; i++) {
                    _addToMap(SA, markers, tmMatchesMap, i, pattern->size(), (patternLength / sizeof(INDEX_CHARACTER_TYPE)) -1, offset);
                } 
                // from right
                for (saidx_t i = left+size; i < prevLeft+prevSize; i++) {
                    _addToMap(SA, markers, tmMatchesMap, i, pattern->size(), (patternLength / sizeof(INDEX_CHARACTER_TYPE)) -1, offset);                    
                } 
                
            }
        } while (patternLength < currentPattern->size() && size > 0);

        if (size > 0) {
            for (saidx_t i = left; i < left+size; i++) {
                _addToMap(SA, markers, tmMatchesMap, i, pattern->size(), patternLength / sizeof(INDEX_CHARACTER_TYPE), offset);
            } 
        }
    }

    return tmMatchesMap;
}

boost::ptr_vector<SubstringOccurence> AnubisSearcher::lcpSearch(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                boost::shared_ptr<std::vector<sauchar_t> > pattern,
                SUFFIX_MARKER_TYPE & length)
                                                 throw(ConcordiaException) {
    saidx_t patternLength = 0;
    saidx_t size = SA->size();
    saidx_t left = 0;

    sauchar_t * patternArray = pattern->data();

    saidx_t * SAleft = SA->data();

    saidx_t prevLeft;
    saidx_t prevSize;
    do {
        prevLeft = left;
        prevSize = size;

        patternLength += sizeof(INDEX_CHARACTER_TYPE);

        saidx_t localLeft;
        size = sa_search(T->data(), (saidx_t) T->size(),
                             (const sauchar_t *) patternArray, patternLength,
                             SAleft, size, &localLeft);        
        left += localLeft;
        SAleft += localLeft;
    } while (patternLength < pattern->size() && size > 0);

    boost::ptr_vector<SubstringOccurence> result;

    if (size == 0) {
        // The search managed to find exactly the longest common prefixes.
        
        length = patternLength - sizeof(INDEX_CHARACTER_TYPE);
        if (length > 0) {
            // Get the results of the previous search
            _collectResults(result, markers, SA, prevLeft, prevSize);
        }
        // If length == 0, then the pattern has no common prefixes
        // with the index.
    } else {
        // Seemingly, the index contains at least one utterance
        // of the whole search pattern.
        length = patternLength;
        _collectResults(result, markers, SA, left, size);
    }

    return result;
}

void AnubisSearcher::_collectResults(
                 boost::ptr_vector<SubstringOccurence> & result,
                 boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                 boost::shared_ptr<std::vector<saidx_t> > SA,
                 saidx_t left, saidx_t size) {
    for (saidx_t i = 0; i < size; i++) {
        saidx_t resultPos = SA->at(left + i);
        
        if (resultPos % sizeof(INDEX_CHARACTER_TYPE) == 0) {
            SUFFIX_MARKER_TYPE marker = markers->at(resultPos / sizeof(INDEX_CHARACTER_TYPE));
            result.push_back(new SubstringOccurence(marker));
        }
    }
}

void AnubisSearcher::_addToMap(boost::shared_ptr<std::vector<saidx_t> > SA,
                               boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                               boost::shared_ptr<TmMatchesMap> tmMatchesMap,
                               saidx_t sa_pos,
                               SUFFIX_MARKER_TYPE totalPatternLength,
                               SUFFIX_MARKER_TYPE matchedFragmentLength,
                               SUFFIX_MARKER_TYPE patternOffset) {
    SubstringOccurence occurence;
    if (_getOccurenceFromSA(SA, markers, sa_pos, occurence)) {
        _addOccurenceToMap(tmMatchesMap,
                           occurence,
                           totalPatternLength,
                           matchedFragmentLength,
                           patternOffset);
    }
}                               


bool AnubisSearcher::_getOccurenceFromSA(
                            boost::shared_ptr<std::vector<saidx_t> > SA,
                            boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                            saidx_t sa_pos,
                            SubstringOccurence & occurence) {
        saidx_t resultPos = SA->at(sa_pos);
        
        if (resultPos % sizeof(INDEX_CHARACTER_TYPE) == 0) {
            SUFFIX_MARKER_TYPE marker = markers->at(resultPos / sizeof(INDEX_CHARACTER_TYPE));
            occurence.enterDataFromMarker(marker);
        }
    
}

void AnubisSearcher::_addOccurenceToMap(boost::shared_ptr<TmMatchesMap> tmMatchesMap,
                        SubstringOccurence & occurence,
                        SUFFIX_MARKER_TYPE totalPatternLength,
                        SUFFIX_MARKER_TYPE matchedFragmentLength,
                        SUFFIX_MARKER_TYPE patternOffset) {
    TmMatches * tmMatches;

    TmMatchesMapIterator mapIterator = tmMatchesMap->find(
        occurence.getId());
    if (mapIterator != tmMatchesMap->end()) {
        tmMatches = mapIterator->second;
    } else {
        tmMatches = new TmMatches(occurence.getId(),
                                  occurence.getExampleLength(),
                                  totalPatternLength);
        SUFFIX_MARKER_TYPE key = occurence.getId();
        tmMatchesMap->insert(key, tmMatches);
    }
    
    // add intervals to tmMatches
    tmMatches->addExampleInterval(
                                  occurence.getOffset(),
                                  occurence.getOffset() + matchedFragmentLength
                                 );
    tmMatches->addPatternInterval(
                                  patternOffset,
                                  patternOffset + matchedFragmentLength
                                 );
    
}

