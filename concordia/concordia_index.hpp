#ifndef CONCORDIA_INDEX_HDR
#define CONCORDIA_INDEX_HDR

#include <divsufsort.h>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"

/*!
  Class for creating and maintaining the index.

*/

using namespace std;

class ConcordiaIndex {
public:
    explicit ConcordiaIndex(const string & wordMapFilepath,
                            const string & hashedIndexFilepath,
                            const string & suffixArrayFilepath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaIndex();

    void addSentence(const string & sentence);

    void serializeWordMap();

    void generateSuffixArray();

private:
    boost::shared_ptr<HashGenerator> _hashGenerator;

    fstream _hashedIndexFile;

    ofstream _suffixArrayFile;
};

#endif
