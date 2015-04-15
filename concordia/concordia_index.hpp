#ifndef CONCORDIA_INDEX_HDR
#define CONCORDIA_INDEX_HDR

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "concordia/common/config.hpp"
#include "concordia/example.hpp"
#include "concordia/hash_generator.hpp"
#include "concordia/concordia_exception.hpp"
#include <divsufsort.h>

/*!
  Class for creating and maintaining the index.

*/

class ConcordiaIndex {
public:
    explicit ConcordiaIndex(const std::string & hashedIndexFilePath,
                            const std::string & markersFilePath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~ConcordiaIndex();

    void addExample(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                const Example & example);

    void addAllExamples(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                const std::vector<Example> & examples);

    boost::shared_ptr<std::vector<saidx_t> > generateSuffixArray(
                boost::shared_ptr<std::vector<sauchar_t> > T);

private:
    // Add example to disk index and update RAM index.
    void _addSingleExample(std::ofstream & hashedIndexFile,
                std::ofstream & markersFile,
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                const Example & example);

    std::string _hashedIndexFilePath;

    std::string _markersFilePath;
};

#endif
