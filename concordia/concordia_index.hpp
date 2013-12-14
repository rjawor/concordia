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
    explicit ConcordiaIndex(const string & hashedIndexFilePath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaIndex();

    void addSentence(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                const string & sentence);

    void addAllSentences(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                boost::shared_ptr<vector<string> > sentences);

    boost::shared_ptr<vector<saidx_t> > generateSuffixArray(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T);

private:
    // Add sentence to disk index and update RAM index.
    void _addSingleSentence(ofstream & hashedIndexFile,
                            boost::shared_ptr<HashGenerator> hashGenerator,
                            boost::shared_ptr<std::vector<sauchar_t> > T,
                            const string & sentence);

    string _hashedIndexFilePath;
};

#endif
