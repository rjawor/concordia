#ifndef INDEX_SEARCHER_HDR
#define INDEX_SEARCHER_HDR

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fstream>
#include <iostream>

#include "concordia/common/config.hpp"
#include "concordia/substring_occurence.hpp"
#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"
#include "concordia/anubis_search_result.hpp"

#include "divsufsort.h"

/*!
  Class for searching the index with a sentence.

*/

using namespace std;

class IndexSearcher {
public:
    explicit IndexSearcher();

    /*! Destructor.
    */
    virtual ~IndexSearcher();

    boost::ptr_vector<SubstringOccurence> simpleSearch(
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const string & pattern) throw(ConcordiaException);

    boost::ptr_vector<AnubisSearchResult> anubisSearch(
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const string & pattern) throw(ConcordiaException);
private:
};

#endif
