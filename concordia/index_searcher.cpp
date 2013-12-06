#include "concordia/index_searcher.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>

IndexSearcher::IndexSearcher():
                    _T(NULL),
                    _SA(NULL),
                    _n(0) {
}


IndexSearcher::~IndexSearcher() {
}


void IndexSearcher::loadIndex(const string & wordMapFilepath,
                            const string & hashedIndexFilepath,
                            const string & suffixArrayFilepath)
                                         throw(ConcordiaException) {
    if (!boost::filesystem::exists(wordMapFilepath)) {
        throw ConcordiaException("E06: Failed to open word map "
                                    "file for reading.");
    }

    if (!boost::filesystem::exists(hashedIndexFilepath)) {
        throw ConcordiaException("E07: Failed to open hashed index file "
                                 "for reading.");
    }

    if (!boost::filesystem::exists(suffixArrayFilepath)) {
        throw ConcordiaException("E08: Failed to open suffix array file "
                                 "for reading.");
    }

    _hashGenerator = boost::shared_ptr<HashGenerator>(
                            new HashGenerator(wordMapFilepath));

    ifstream hashedIndexFile;
    hashedIndexFile.open(hashedIndexFilepath.c_str(), ios::in
                                                | ios::ate | ios::binary);
    _n = hashedIndexFile.tellg();
    hashedIndexFile.seekg(0, ios::beg);
    _T = new sauchar_t[_n];
    int pos = 0;
    while (!hashedIndexFile.eof()) {
        INDEX_CHARACTER_TYPE character =
                         Utils::readIndexCharacter(hashedIndexFile);
        Utils::insertCharToSaucharArray(_T, character, pos);
        pos+=sizeof(character);
    }
    hashedIndexFile.close();

    _SA = new saidx_t[_n];

    ifstream suffixArrayFile;
    suffixArrayFile.open(suffixArrayFilepath.c_str(), ios::in | ios::binary);

    saidx_t saidx_buff;
    pos = 0;
    while (!suffixArrayFile.eof() && pos < _n) {
        suffixArrayFile.read(reinterpret_cast<char *>(&saidx_buff),
                                                  sizeof(saidx_t));
        _SA[pos++] = saidx_buff;
    }
    suffixArrayFile.close();
}

vector<saidx_t> IndexSearcher::simpleSearch(const string & pattern)
                                            throw(ConcordiaException) {
    vector<saidx_t> result;

    int left;
    vector<INDEX_CHARACTER_TYPE> hash = _hashGenerator->generateHash(pattern);
    saidx_t patternLength = hash.size()*sizeof(INDEX_CHARACTER_TYPE);
    sauchar_t * patternArray = Utils::indexVectorToSaucharArray(hash);
    int size = sa_search(_T, (saidx_t) _n,
               (const sauchar_t *) patternArray, patternLength,
               _SA, (saidx_t) _n, &left);
    for (int i = 0; i < size; ++i) {
        saidx_t result_pos = _SA[left + i];
        if (result_pos % sizeof(INDEX_CHARACTER_TYPE) == 0) {
        // As we are looking for a pattern in an array of higher
        // resolution than the hashed index file, we might
        // obtain accidental results exceeding the boundaries
        // of characters in hashed index. The above check
        // removes these accidental results.
            result.push_back(result_pos / sizeof(INDEX_CHARACTER_TYPE));
        }
    }

    delete[] patternArray;
    return result;
}




