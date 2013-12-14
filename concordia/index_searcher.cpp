#include "concordia/index_searcher.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>

IndexSearcher::IndexSearcher() {
}


IndexSearcher::~IndexSearcher() {
}

boost::shared_ptr<vector<saidx_t> > IndexSearcher::simpleSearch(
                      boost::shared_ptr<HashGenerator> hashGenerator,
                      boost::shared_ptr<std::vector<sauchar_t> > T,
                      boost::shared_ptr<std::vector<saidx_t> > SA,
                      const string & pattern) throw(ConcordiaException) {
    boost::shared_ptr<vector<saidx_t> > result =
                    boost::shared_ptr<vector<saidx_t> >(new vector<saidx_t>());

    int left;
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash =
                                          hashGenerator->generateHash(pattern);
    saidx_t patternLength = hash->size()*sizeof(INDEX_CHARACTER_TYPE);
    sauchar_t * patternArray = Utils::indexVectorToSaucharArray(hash);
    int size = sa_search(T->data(), (saidx_t) T->size(),
                         (const sauchar_t *) patternArray, patternLength,
                         SA->data(), (saidx_t) T->size(), &left);
    for (int i = 0; i < size; ++i) {
        saidx_t result_pos = SA->at(left + i);
        if (result_pos % sizeof(INDEX_CHARACTER_TYPE) == 0) {
        // As we are looking for a pattern in an array of higher
        // resolution than the hashed index file, we might
        // obtain accidental results exceeding the boundaries
        // of characters in hashed index. The above check
        // removes these accidental results.
            result->push_back(result_pos / sizeof(INDEX_CHARACTER_TYPE));
        }
    }

    delete[] patternArray;
    return result;
}




