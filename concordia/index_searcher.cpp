#include "concordia/index_searcher.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>

IndexSearcher::IndexSearcher() {
    _anubisSearcher = boost::shared_ptr<AnubisSearcher>(
                                   new AnubisSearcher());
}


IndexSearcher::~IndexSearcher() {
}

boost::ptr_vector<SubstringOccurence> IndexSearcher::simpleSearch(
                  boost::shared_ptr<HashGenerator> hashGenerator,
                  boost::shared_ptr<std::vector<sauchar_t> > T,
                  boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                  boost::shared_ptr<std::vector<saidx_t> > SA,
                  const string & pattern) throw(ConcordiaException) {
    boost::ptr_vector<SubstringOccurence> result;

    int left;
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash =
                                          hashGenerator->generateHash(pattern);
    saidx_t patternLength = hash->size()*sizeof(INDEX_CHARACTER_TYPE);
    sauchar_t * patternArray = Utils::indexVectorToSaucharArray(hash);

    int size = sa_search(T->data(), (saidx_t) T->size(),
                         (const sauchar_t *) patternArray, patternLength,
                         SA->data(), (saidx_t) SA->size(), &left);
    for (int i = 0; i < size; ++i) {
        saidx_t resultPos = SA->at(left + i);
        if (resultPos % sizeof(INDEX_CHARACTER_TYPE) == 0) {
        // As we are looking for a pattern in an array of higher
        // resolution than the hashed index file, we might
        // obtain accidental results exceeding the boundaries
        // of characters in hashed index. The above check
        // removes these accidental results.
            saidx_t actualResultPos = resultPos / sizeof(INDEX_CHARACTER_TYPE);
            SUFFIX_MARKER_TYPE marker = markers->at(actualResultPos);

            // TODO(rafalj): think about using bitwise operators
            // in the below code
            result.push_back(new SubstringOccurence(
                marker / SUFFIX_MARKER_DIVISOR,
                marker % SUFFIX_MARKER_DIVISOR));
        }
    }

    delete[] patternArray;
    return result;
}

boost::ptr_vector<AnubisSearchResult> IndexSearcher::anubisSearch(
                  boost::shared_ptr<HashGenerator> hashGenerator,
                  boost::shared_ptr<std::vector<sauchar_t> > T,
                  boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                  boost::shared_ptr<std::vector<saidx_t> > SA,
                  const string & pattern) throw(ConcordiaException) {
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash =
                                          hashGenerator->generateHash(pattern);
    return _anubisSearcher->anubisSearch(T, markers, SA, hash);
}
