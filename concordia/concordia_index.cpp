#include "concordia/concordia_index.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

ConcordiaIndex::ConcordiaIndex(const string & wordMapFilePath,
                            const string & hashedIndexFilePath,
                            const string & suffixArrayFilePath)
                                         throw(ConcordiaException) :
                           _hashedIndexFilePath(hashedIndexFilePath),
                           _suffixArrayFilePath(suffixArrayFilePath) {
    if (boost::filesystem::exists(wordMapFilePath)) {
        if (!boost::filesystem::exists(hashedIndexFilePath)) {
            throw ConcordiaException("E01: Word map file exists "
                                     "but hashed index file absent.");
        }
    } else {       // WordMap file does not exist
        if (boost::filesystem::exists(hashedIndexFilePath)) {
            throw ConcordiaException("E02: Hashed index file exists "
                                     "but word map file absent.");
        }
    }
    _hashGenerator = boost::shared_ptr<HashGenerator>(
                                    new HashGenerator(wordMapFilePath));
}

ConcordiaIndex::~ConcordiaIndex() {
}

void ConcordiaIndex::_serializeWordMap() {
    _hashGenerator->serializeWordMap();
}

void ConcordiaIndex::generateSuffixArray() {
    if (boost::filesystem::exists(_hashedIndexFilePath.c_str())) {
        ifstream hashedIndexFile;
        hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::in|
                                                 ios::ate|ios::binary);

        /* Get the file size. */
        saidx_t n = hashedIndexFile.tellg();
        if (n > 0) {
            sauchar_t *T;
            saidx_t *SA;

            /* Read n bytes of data. */
            hashedIndexFile.seekg(0, ios::beg);
            T = new sauchar_t[n];
            int pos = 0;
            while (!hashedIndexFile.eof()) {
                INDEX_CHARACTER_TYPE character =
                             Utils::readIndexCharacter(hashedIndexFile);
                Utils::insertCharToSaucharArray(T, character, pos);
                pos+=sizeof(character);
            }
            hashedIndexFile.close();

            SA = new saidx_t[n];

            /* Construct the suffix array. */
            if (divsufsort(T, SA, (saidx_t)n) != 0) {
                throw ConcordiaException("Error creating suffix array.");
            }

            /* Write the suffix array. */

            ofstream suffixArrayFile;
            suffixArrayFile.open(_suffixArrayFilePath.c_str(),
                                                     ios::out|ios::binary);

            for (int i = 0; i < n; i++) {
                suffixArrayFile.write(reinterpret_cast<char *>(&SA[i]),
                                                          sizeof(saidx_t));
            }
            suffixArrayFile.close();

            /* Deallocate memory. */
            delete[] T;
            delete[] SA;
        }  else {
            throw ConcordiaException("Can not generate suffix array: "
                                       "hashed index file is empty");
        }
    } else {
        throw ConcordiaException("Can not generate suffix array: "
                                 "hashed index file does not exist");
    }
}

void ConcordiaIndex::addSentence(const string & sentence) {
    vector<INDEX_CHARACTER_TYPE> hash = _hashGenerator->generateHash(sentence);
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    for (vector<INDEX_CHARACTER_TYPE>::iterator it = hash.begin();
                                          it != hash.end(); ++it) {
        Utils::writeIndexCharacter(hashedIndexFile, *it);
    }
    hashedIndexFile.close();
    _serializeWordMap();
}

void ConcordiaIndex::addAllSentences(vector<std::string> & sentences) {
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    for (vector<string>::iterator sent_it = sentences.begin();
                                   sent_it != sentences.end(); ++sent_it) {
        string sentence = *sent_it;
        vector<INDEX_CHARACTER_TYPE> hash =
                                     _hashGenerator->generateHash(sentence);
        for (vector<INDEX_CHARACTER_TYPE>::iterator it = hash.begin();
                                              it != hash.end(); ++it) {
            Utils::writeIndexCharacter(hashedIndexFile, *it);
        }
    }
    hashedIndexFile.close();
    _serializeWordMap();
}

