#ifndef CONCORDIA_INDEX_HDR
#define CONCORDIA_INDEX_HDR

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

#include "concordia/common/config.hpp"
#include "concordia/example.hpp"
#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"
#include "divsufsort.h"

/*!
  Class for creating and maintaining the index.

*/

using namespace std;

class ConcordiaIndex {
public:
    explicit ConcordiaIndex(const string & hashedIndexFilePath,
                            const string & markersFilePath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaIndex();

    void addExample(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                const Example & example);

    void addAllExamples(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                const boost::ptr_vector<Example > & examples);

    boost::shared_ptr<vector<saidx_t> > generateSuffixArray(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T);

private:
    // Add example to disk index and update RAM index.
    void _addSingleExample(ofstream & hashedIndexFile,
                        ofstream & markersFile,
                        boost::shared_ptr<HashGenerator> hashGenerator,
                        boost::shared_ptr<std::vector<sauchar_t> > T,
                        boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                        const Example & example);

    string _hashedIndexFilePath;

    string _markersFilePath;
};

#endif
