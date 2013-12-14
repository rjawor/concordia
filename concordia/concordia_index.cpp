#include "concordia/concordia_index.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

ConcordiaIndex::ConcordiaIndex(const string & hashedIndexFilePath)
                                         throw(ConcordiaException) :
                           _hashedIndexFilePath(hashedIndexFilePath) {
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

void ConcordiaIndex::addSentence(boost::shared_ptr<HashGenerator> hashGenerator,
                boost::shared_ptr<vector<sauchar_t> > T,
                const string & sentence) {
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    _addSingleSentence(hashedIndexFile, hashGenerator, T, sentence);
    hashedIndexFile.close();
    hashGenerator->serializeWordMap();
}

void ConcordiaIndex::addAllSentences(
                        boost::shared_ptr<HashGenerator> hashGenerator,
                        boost::shared_ptr<vector<sauchar_t> > T,
                        boost::shared_ptr<vector<string> > sentences) {
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    for (vector<string>::iterator sent_it = sentences->begin();
                                   sent_it != sentences->end(); ++sent_it) {
        string sentence = *sent_it;
        _addSingleSentence(hashedIndexFile, hashGenerator, T, sentence);
    }
    hashedIndexFile.close();
    hashGenerator->serializeWordMap();
}

void ConcordiaIndex::_addSingleSentence(
                                ofstream & hashedIndexFile,
                                boost::shared_ptr<HashGenerator> hashGenerator,
                                boost::shared_ptr<std::vector<sauchar_t> > T,
                                const string & sentence) {
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash
                             = hashGenerator->generateHash(sentence);
    for (vector<INDEX_CHARACTER_TYPE>::iterator it = hash->begin();
                                          it != hash->end(); ++it) {
        INDEX_CHARACTER_TYPE character = *it;
        Utils::writeIndexCharacter(hashedIndexFile, character);
        Utils::appendCharToSaucharVector(T, character);
    }
}

