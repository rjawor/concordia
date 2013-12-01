#include "concordia/concordia_index.hpp"

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

void ConcordiaIndex::serializeWordMap() {
    _hashGenerator->serializeWordMap();
}

void ConcordiaIndex::generateSuffixArray() {
    ifstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::in|
                                             ios::ate|ios::binary);

    /* Get the file size. */
    long n = hashedIndexFile.tellg() / sizeof(sauchar_t);

    sauchar_t *T;
    saidx_t *SA;

    T = new sauchar_t[n];
    SA = new saidx_t[n];

    /* Read n bytes of data. */
    hashedIndexFile.seekg(0, ios::beg);

    sauchar_t buff;
    int pos = 0;
    while (!hashedIndexFile.eof()) {
        hashedIndexFile.read(reinterpret_cast<char *>(&buff),
                                                 sizeof(sauchar_t));
        T[pos++] = buff;
    }
    hashedIndexFile.close();

    /* Construct the suffix array. */
    if (divsufsort(T, SA, (saidx_t)n) != 0) {
        throw ConcordiaException("Error creating suffix array.");
    }

    /* Write the suffix array. */

    ofstream suffixArrayFile;
    suffixArrayFile.open(_suffixArrayFilePath.c_str(), ios::out|ios::binary);

    for (int i = 0; i < n; i++) {
        suffixArrayFile.write(reinterpret_cast<char *>(&SA[i]),
                                                         sizeof(saidx_t));
    }
    suffixArrayFile.close();

    /* Deallocate memory. */
    delete[] T;
    delete[] SA;
}

void ConcordiaIndex::addSentence(const string & sentence) {
    vector<sauchar_t> hash = _hashGenerator->generateHash(sentence);
    ofstream hashedIndexFile;
    hashedIndexFile.open(_hashedIndexFilePath.c_str(), ios::out|
                                                     ios::app|ios::binary);
    for (vector<sauchar_t>::iterator it = hash.begin();
                                          it != hash.end(); ++it) {
        sauchar_t buff = *it;
        hashedIndexFile.write(reinterpret_cast<char *>(&buff),
                                                        sizeof(sauchar_t));
    }
    hashedIndexFile.close();
}

