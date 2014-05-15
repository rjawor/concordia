#ifndef ANUBIS_SEARCHER_HDR
#define ANUBIS_SEARCHER_HDR

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/concordia_exception.hpp"
#include "concordia/anubis_search_result.hpp"

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

    boost::ptr_vector<AnubisSearchResult> anubisSearch(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                boost::shared_ptr<std::vector<INDEX_CHARACTER_TYPE> > pattern)
                                                     throw(ConcordiaException);

    boost::ptr_vector<SubstringOccurence> lcpSearch(
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    boost::shared_ptr<std::vector<sauchar_t> > pattern,
                    SUFFIX_MARKER_TYPE & length) throw(ConcordiaException);

private:
    void _collectResults(boost::ptr_vector<SubstringOccurence> & result,
                 boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                 boost::shared_ptr<std::vector<saidx_t> > SA,
                 saidx_t left, saidx_t size);
};

#endif