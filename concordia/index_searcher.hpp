#ifndef INDEX_SEARCHER_HDR
#define INDEX_SEARCHER_HDR

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>

#include "concordia/common/config.hpp"
#include "build/libdivsufsort/include/divsufsort.h"
#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"

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

    boost::shared_ptr<vector<saidx_t> > simpleSearch(
                    boost::shared_ptr<HashGenerator> hashGenerator,
                    boost::shared_ptr<std::vector<sauchar_t> > T,
                    boost::shared_ptr<std::vector<saidx_t> > SA,
                    const string & pattern) throw(ConcordiaException);
private:
};

#endif
