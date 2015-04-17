#ifndef INDEX_SEARCHER_HDR
#define INDEX_SEARCHER_HDR

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "concordia/common/config.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"
#include "concordia/anubis_searcher.hpp"
#include "concordia/anubis_search_result.hpp"

#include <divsufsort.h>

/*!
  Class for searching the index with a sentence.

*/

class IndexSearcher {
public:
    explicit IndexSearcher();

    /*! Destructor.
    */
    virtual ~IndexSearcher();

    std::vector<SubstringOccurence> simpleSearch(
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const std::string & pattern) throw(ConcordiaException);

    std::vector<AnubisSearchResult> anubisSearch(
                    boost::shared_ptr<ConcordiaConfig> config,
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const std::string & pattern) throw(ConcordiaException);

    boost::shared_ptr<ConcordiaSearchResult> concordiaSearch(
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const std::string & pattern) throw(ConcordiaException);

private:
    boost::shared_ptr<AnubisSearcher> _anubisSearcher;
};

#endif
