#include "concordia/concordia_index.hpp"

#include <boost/filesystem.hpp>

ConcordiaIndex::ConcordiaIndex(const string & wordMapFilepath,
                            const string & hashedIndexFilepath,
                            const string & suffixArrayFilepath)
                                         throw(ConcordiaException) {
    if (boost::filesystem::exists(wordMapFilepath)) {
        if (boost::filesystem::exists(hashedIndexFilepath)) {
            // create hashed index file for appending
        } else {
            throw ConcordiaException("E01: Word map file exists "
                                     "but hashed index file absent.");
        }
    } else {       // WordMap file does not exist
        if (boost::filesystem::exists(hashedIndexFilepath)) {
            throw ConcordiaException("E02: Hashed index file exists "
                                     "but word map file absent.");
        } else {
            // create hashed index file for writing
        }
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
}

void ConcordiaIndex::addSentence(const string & sentence) {
}

