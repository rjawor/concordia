#include "concordia/anubis_searcher.hpp"
#include "concordia/tm_matches.hpp"
#include "concordia/common/logging.hpp"

#include <boost/ptr_container/ptr_map.hpp>
#include <boost/assign/ptr_map_inserter.hpp> 
#include <boost/foreach.hpp>
#include <iostream>
#include <map>

typedef boost::ptr_map<SUFFIX_MARKER_TYPE, TmMatches> TmMatchesMap;
typedef TmMatchesMap::iterator TmMatchesMapIterator;

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
    SET_LOGGER_FILE("/tmp/concordia.log");
    SET_LOGGING_LEVEL("ERROR");
    INFO("AnubisSearcher::anubisSearch");

    boost::ptr_vector<AnubisSearchResult> result;

    boost::shared_ptr<std::vector<sauchar_t> > patternVector =
        Utils::indexVectorToSaucharVector(pattern);

    if (patternVector->size() !=
        pattern->size() * sizeof(INDEX_CHARACTER_TYPE)) {
        throw ConcordiaException("Increasing pattern resolution went wrong.");
    }

    INFO("AnubisSearcher::anubisSearch - about to create tmMatchesMap");
    TmMatchesMap tmMatchesMap;
    for (int offset = 0; offset < pattern->size(); offset++) {
        INFO("AnubisSearcher::anubisSearch - offset: ");
        INFO(offset);

        int highResOffset = offset * sizeof(INDEX_CHARACTER_TYPE);
        INFO("AnubisSearcher::anubisSearch - high res offset: ");
        INFO(highResOffset);
        boost::shared_ptr<std::vector<sauchar_t> > currentPattern =
            boost::shared_ptr<std::vector<sauchar_t> >
            (new std::vector<sauchar_t>(
            patternVector->begin()+highResOffset, patternVector->end()));
        SUFFIX_MARKER_TYPE highResLongestPrefixesLength;
        INFO("AnubisSearcher::anubisSearch - about to get longest prefixes");
        boost::ptr_vector<SubstringOccurence> longestPrefixes =
            lcpSearch(T, markers, SA, currentPattern, highResLongestPrefixesLength);
        
        INFO("AnubisSearcher::anubisSearch - longest prefixes got");
        SUFFIX_MARKER_TYPE longestPrefixesLength = highResLongestPrefixesLength / 
                                                   sizeof(INDEX_CHARACTER_TYPE);
        INFO("AnubisSearcher::anubisSearch - longest prefixes high res length");
        INFO(highResLongestPrefixesLength);
        INFO("AnubisSearcher::anubisSearch - longest prefixes length");
        INFO(longestPrefixesLength);

        if (longestPrefixesLength > 0) {
            BOOST_FOREACH(SubstringOccurence & occurence, longestPrefixes) {
                boost::shared_ptr<TmMatches> tmMatches;

                TmMatchesMapIterator mapIterator = tmMatchesMap.find(
                    occurence.getId());
                if (mapIterator != tmMatchesMap.end()) {
                    tmMatches = boost::shared_ptr<TmMatches>(
                                    mapIterator->second
                                );
                } else {
                    tmMatches = boost::shared_ptr<TmMatches>(
                                                 new TmMatches(
                                                     occurence.getId(),
                                                     occurence.getExampleLength(),
                                                     patternVector->size() 
                                                 ));
                }
                
                // add intervals to tmMatches
                tmMatches->addExampleInterval(
                                              occurence.getOffset(),
                                              occurence.getOffset() + longestPrefixesLength
                                             );
                tmMatches->addPatternInterval(
                                              offset,
                                              offset + longestPrefixesLength
                                             );
            }
        }
    }
    
    // get the tmMatches list sorted descending by score

    return result;
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
