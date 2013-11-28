#include "concordia/index_searcher.hpp"

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
    _T = new sauchar_t[_n];

    hashedIndexFile.seekg(0, ios::beg);
    hashedIndexFile.read(reinterpret_cast<char*> (_T), _n);
    hashedIndexFile.close();

    _SA = new saidx_t[_n];

    ifstream suffixArrayFile;
    suffixArrayFile.open(suffixArrayFilepath.c_str(), ios::in | ios::binary);

    saidx_t buff;
    int pos = 0;
    while (!suffixArrayFile.eof() && pos < _n) {
        suffixArrayFile.read(reinterpret_cast<char *>(&buff), sizeof(saidx_t));
        _SA[pos++] = buff;
    }
    suffixArrayFile.close();
}

vector<saidx_t> IndexSearcher::simpleSearch(const string & pattern)
                                            throw(ConcordiaException) {
    vector<saidx_t> result;

    int left;
    vector<sauchar_t> hash = _hashGenerator->generateHash(pattern);
    saidx_t patternLength = hash.size();
    sauchar_t * patternArray = new sauchar_t[patternLength];
    int i = 0;
    for (vector<sauchar_t>::iterator it = hash.begin();
                                          it != hash.end(); ++it) {
        patternArray[i] = *it;
        i++;
    }

    int size = sa_search(_T, (saidx_t) _n,
               (const sauchar_t *) patternArray, patternLength,
               _SA, (saidx_t) _n, &left);
    for (i = 0; i < size; ++i) {
        result.push_back(_SA[left + i]);
    }

    delete[] patternArray;
    return result;
}




