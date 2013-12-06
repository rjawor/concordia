#ifndef CONCORDIA_INDEX_HDR
#define CONCORDIA_INDEX_HDR

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"
#include "build/libdivsufsort/include/divsufsort.h"

/*!
  Class for creating and maintaining the index.

*/

using namespace std;

class ConcordiaIndex {
public:
    explicit ConcordiaIndex(const string & wordMapFilePath,
                            const string & hashedIndexFilePath,
                            const string & suffixArrayFilePath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaIndex();

    void addSentence(const string & sentence);

    void addAllSentences(vector<string> & sentences);

    void generateSuffixArray();

private:
    void _serializeWordMap();

    boost::shared_ptr<HashGenerator> _hashGenerator;

    string _hashedIndexFilePath;

    string _suffixArrayFilePath;
};

#endif
