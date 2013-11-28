#ifndef INDEX_SEARCHER_HDR
#define INDEX_SEARCHER_HDR

#include <divsufsort.h>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>

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

    void loadIndex(const string & wordMapFilepath,
                            const string & hashedIndexFilepath,
                            const string & suffixArrayFilepath)
                                      throw(ConcordiaException);

    vector<saidx_t> simpleSearch(const string & pattern)
                                      throw(ConcordiaException);

private:
    boost::shared_ptr<HashGenerator> _hashGenerator;

    sauchar_t * _T;

    saidx_t * _SA;

    size_t _n;
};

#endif
