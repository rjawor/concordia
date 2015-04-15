#ifndef ANUBIS_SEARCHER_HDR
#define ANUBIS_SEARCHER_HDR

#include <boost/shared_ptr.hpp>

#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/concordia_exception.hpp"
#include "concordia/anubis_search_result.hpp"
#include "concordia/tm_matches.hpp"

#include <divsufsort.h>

/*!
  Class for searching using Anubis algorithm.

*/

using namespace std;

class AnubisSearcher {
public:
    explicit AnubisSearcher();

    /*! Destructor.
    */
    virtual ~AnubisSearcher();

    std::vector<AnubisSearchResult> anubisSearch(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                const std::vector<INDEX_CHARACTER_TYPE> & pattern)
                                                     throw(ConcordiaException);

    boost::shared_ptr<TmMatchesMap> getTmMatches(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                const std::vector<INDEX_CHARACTER_TYPE> & pattern)
                                                     throw(ConcordiaException);

    std::vector<SubstringOccurence> lcpSearch(
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const std::vector<sauchar_t> & pattern,
                    SUFFIX_MARKER_TYPE & length) throw(ConcordiaException);

private:
    void _collectResults(vector<SubstringOccurence> & result,
                 boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                 boost::shared_ptr<std::vector<saidx_t> > SA,
                 saidx_t left, saidx_t size);

    void _addToMap(boost::shared_ptr<std::vector<saidx_t> > SA,
                   boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                   boost::shared_ptr<TmMatchesMap> tmMatchesMap,
                   saidx_t sa_pos,
                   SUFFIX_MARKER_TYPE totalPatternLength,
                   SUFFIX_MARKER_TYPE matchedFragmentLength,
                   SUFFIX_MARKER_TYPE patternOffset);

    bool _getOccurenceFromSA(boost::shared_ptr<std::vector<saidx_t> > SA,
                             boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                             saidx_t sa_pos,
                             SubstringOccurence & occurence);

    void _addOccurenceToMap(boost::shared_ptr<TmMatchesMap> tmMatchesMap,
                            SubstringOccurence & occurence,
                            SUFFIX_MARKER_TYPE totalPatternLength,
                            SUFFIX_MARKER_TYPE matchedFragmentLength,
                            SUFFIX_MARKER_TYPE patternOffset);
};

#endif
