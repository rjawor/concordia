#include "concordia/anubis_searcher.hpp"
#include "concordia/tm_matches.hpp"

#include <boost/ptr_container/ptr_map.hpp>
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
    boost::ptr_vector<AnubisSearchResult> result;

    boost::shared_ptr<std::vector<sauchar_t> > patternVector =
        Utils::indexVectorToSaucharVector(pattern);

    if (patternVector->size() !=
        pattern->size() * sizeof(INDEX_CHARACTER_TYPE)) {
        throw ConcordiaException("Increasing pattern resolution went wrong.");
    }

    TmMatchesMap tmMatchesMap;
    for (int offset = 0; offset < pattern->size(); offset++) {
        int highResOffset = offset * sizeof(INDEX_CHARACTER_TYPE);
        boost::shared_ptr<std::vector<sauchar_t> > currentPattern =
            boost::shared_ptr<std::vector<sauchar_t> >
            (new std::vector<sauchar_t>(
            patternVector->begin()+highResOffset, patternVector->end()));
        SUFFIX_MARKER_TYPE longestPrefixesLength;
        boost::ptr_vector<SubstringOccurence> longestPrefixes =
            lcpSearch(T, markers, SA, currentPattern, longestPrefixesLength);

        BOOST_FOREACH(SubstringOccurence & occurence, longestPrefixes) {
            TmMatchesMapIterator mapIterator = tmMatchesMap.find(
                occurence.getId());
            if (mapIterator != tmMatchesMap.end()) {
            }
        }
    }

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

        patternLength++;

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
        length = patternLength - 1;
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
        SUFFIX_MARKER_TYPE marker = markers->at(resultPos);
        result.push_back(new SubstringOccurence(
                            marker / SUFFIX_MARKER_DIVISOR,
                            marker % SUFFIX_MARKER_DIVISOR));
    }
}
