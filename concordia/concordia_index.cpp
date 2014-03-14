#include "concordia/concordia_index.hpp"

#include "concordia/common/utils.hpp"
#include "concordia/common/config.hpp"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <iostream>

ConcordiaIndex::ConcordiaIndex(const string & hashedIndexFilePath,
                               const string & markersFilePath)
                                         throw(ConcordiaException) :
                           _hashedIndexFilePath(hashedIndexFilePath),
                           _markersFilePath(markersFilePath) {
}

ConcordiaIndex::~ConcordiaIndex() {
}

boost::shared_ptr<vector<saidx_t> > ConcordiaIndex::generateSuffixArray(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T) {
    saidx_t * SA_array = new saidx_t[T->size()];
    if (divsufsort(T->data(), SA_array, (saidx_t) T->size()) != 0) {
        throw ConcordiaException("Error creating suffix array.");
    }

    boost::shared_ptr<vector<saidx_t> > result =
             boost::shared_ptr<vector<saidx_t> >(new vector<saidx_t>);
    for (int i = 0; i < T->size(); i++) {
        result->push_back(SA_array[i]);
    }

    delete[] SA_array;
    return result;
}

void ConcordiaIndex::addExample(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                const Example & example) {
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    ofstream markersFile;
    markersFile.open(_markersFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    _addSingleExample(hashedIndexFile, markersFile, hashGenerator,
                                                      T, markers, example);
    hashedIndexFile.close();
    markersFile.close();
    hashGenerator->serializeWordMap();
}

void ConcordiaIndex::addAllExamples(
                boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                const boost::ptr_vector<Example > & examples) {
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    ofstream markersFile;
    markersFile.open(_markersFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);

    BOOST_FOREACH(Example example, examples) {
        _addSingleExample(hashedIndexFile, markersFile, hashGenerator,
                                                      T, markers, example);
    }

    hashedIndexFile.close();
    markersFile.close();
    hashGenerator->serializeWordMap();
}

void ConcordiaIndex::_addSingleExample(
                        ofstream & hashedIndexFile,
                        ofstream & markersFile,
                        boost::shared_ptr<HashGenerator> hashGenerator,
                        boost::shared_ptr<std::vector<sauchar_t> > T,
                        boost::shared_ptr<vector<SUFFIX_MARKER_TYPE> > markers,
                        const Example & example) {
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash
                          = hashGenerator->generateHash(example.getSentence());
    int offset = 0;
    for (vector<INDEX_CHARACTER_TYPE>::iterator it = hash->begin();
                                          it != hash->end(); ++it) {
        INDEX_CHARACTER_TYPE character = *it;
        Utils::writeIndexCharacter(hashedIndexFile, character);
        Utils::appendCharToSaucharVector(T, character);

        // append to markersFile

        SUFFIX_MARKER_TYPE marker = offset;
        marker += example.getId() * SUFFIX_MARKER_DIVISOR;

        Utils::writeMarker(markersFile, marker);
        markers->push_back(marker);

        offset++;
    }

    // append sentence boundary marker
    INDEX_CHARACTER_TYPE sentenceBoundaryHI = INDEX_CHARACTER_TYPE_MAX_VALUE;
    Utils::writeIndexCharacter(hashedIndexFile, sentenceBoundaryHI);
    Utils::appendCharToSaucharVector(T, sentenceBoundaryHI);

    SUFFIX_MARKER_TYPE sentenceBoundaryMA = SUFFIX_MARKER_TYPE_MAX_VALUE;
    Utils::writeMarker(markersFile, sentenceBoundaryMA);
    markers->push_back(sentenceBoundaryMA);
}

