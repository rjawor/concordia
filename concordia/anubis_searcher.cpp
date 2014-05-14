#include "concordia/anubis_searcher.hpp"


AnubisSearcher::AnubisSearcher() {
}


AnubisSearcher::~AnubisSearcher() {
}


boost::ptr_vector<AnubisSearchResult> AnubisSearcher::anubisSearch(
                boost::shared_ptr<std::vector<sauchar_t> > T,
                boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers,
                boost::shared_ptr<std::vector<saidx_t> > SA,
                boost::shared_ptr<std::vector<INDEX_CHARACTER_TYPE> >) 
                                                throw(ConcordiaException) {

    boost::ptr_vector<AnubisSearchResult> result;
    return result;
}
