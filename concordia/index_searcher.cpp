#include "concordia/index_searcher.hpp"

#include "concordia/common/utils.hpp"
#include <boost/filesystem.hpp>

IndexSearcher::IndexSearcher() {
    _anubisSearcher = boost::shared_ptr<AnubisSearcher>(
                                   new AnubisSearcher());
}


IndexSearcher::~IndexSearcher() {
}

std::vector<SubstringOccurence> IndexSearcher::simpleSearch(
                  boost::shared_ptr<HashGenerator> hashGenerator,
                  boost::shared_ptr<std::vector<sauchar_t> > T,
                  boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                  boost::shared_ptr<std::vector<saidx_t> > SA,
                  const std::string & pattern) throw(ConcordiaException) {
    std::vector<SubstringOccurence> result;

    int left;
    std::vector<INDEX_CHARACTER_TYPE> hash =
                                 hashGenerator->generateHash(pattern);
    saidx_t patternLength = hash.size()*sizeof(INDEX_CHARACTER_TYPE);
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

            result.push_back(SubstringOccurence(marker));
        }
    }

    delete[] patternArray;
    return result;
}

std::vector<AnubisSearchResult> IndexSearcher::anubisSearch(
                  boost::shared_ptr<ConcordiaConfig> config,
                  boost::shared_ptr<HashGenerator> hashGenerator,
                  boost::shared_ptr<std::vector<sauchar_t> > T,
                  boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                  boost::shared_ptr<std::vector<saidx_t> > SA,
                  const std::string & pattern) throw(ConcordiaException) {
    std::vector<INDEX_CHARACTER_TYPE> hash =
                                 hashGenerator->generateHash(pattern);
    return _anubisSearcher->anubisSearch(config, T, markers, SA, hash);
}
