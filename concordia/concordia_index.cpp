#include "concordia/concordia_index.hpp"

#include <boost/filesystem.hpp>

ConcordiaIndex::ConcordiaIndex(const string & wordMapFilepath,
                            const string & hashedIndexFilepath,
                            const string & suffixArrayFilepath)
                                         throw(ConcordiaException) {
    if (boost::filesystem::exists(wordMapFilepath)) {
        if (boost::filesystem::exists(hashedIndexFilepath)) {
            _hashedIndexFile.open(hashedIndexFilepath.c_str(), ios::out |
                                                     ios::app | ios::binary);
            if (!_hashedIndexFile.is_open()) {
                throw ConcordiaException("E03: Failed to open hashed index "
                                            "file for appending.");
            }
        } else {
            throw ConcordiaException("E01: Word map file exists "
                                     "but hashed index file absent.");
        }
    } else {       // WordMap file does not exist
        if (boost::filesystem::exists(hashedIndexFilepath)) {
            throw ConcordiaException("E02: Hashed index file exists "
                                     "but word map file absent.");
        } else {
            _hashedIndexFile.open(hashedIndexFilepath.c_str(), ios::out |
                                                           ios::binary);
            if (!_hashedIndexFile.is_open()) {
                throw ConcordiaException("E04: Failed to open hashed index "
                                            "file for writing.");
            }
        }
    }

    _suffixArrayFile.open(suffixArrayFilepath.c_str(), ios::out |
                                                   ios::binary);
    if (!_hashedIndexFile.is_open()) {
        throw ConcordiaException("E05: Failed to open suffix array "
                                    "file for writing.");
    }
    _hashGenerator = boost::shared_ptr<HashGenerator>(
                                    new HashGenerator(wordMapFilepath));
}

ConcordiaIndex::~ConcordiaIndex() {
}

void ConcordiaIndex::serializeWordMap() {
    _hashGenerator->serializeWordMap();
}

void ConcordiaIndex::generateSuffixArray() {
    /* Get the file size. */
    long n = _hashedIndexFile.tellg();

    /* Allocate 5blocksize bytes of memory. */
    sauchar_t *T;
    saidx_t *SA;

    T = reinterpret_cast<sauchar_t *> (malloc((size_t)n * sizeof(sauchar_t)));
    SA = reinterpret_cast<saidx_t *> (malloc((size_t)n * sizeof(saidx_t)));
    if ((T == NULL) || (SA == NULL)) {
        throw ConcordiaException("Cannot allocate memory.");
    }

    /* Read n bytes of data. */

    _hashedIndexFile.seekg(0, ios::beg);
    _hashedIndexFile.read(reinterpret_cast<char*> (T), (size_t)n);

    /* Construct the suffix array. */
    if (divsufsort(T, SA, (saidx_t)n) != 0) {
        throw ConcordiaException("Error creating suffix array.");
    }

    /* Write the suffix array. */
    _suffixArrayFile << *SA;

    /* Deallocate memory. */
    free(SA);
    free(T);
}

void ConcordiaIndex::addSentence(const string & sentence) {
    vector<sauchar_t> hash = _hashGenerator->generateHash(sentence);
    for (vector<sauchar_t>::iterator it = hash.begin();
                                          it != hash.end(); ++it) {
        _hashedIndexFile << *it;
    }
}

