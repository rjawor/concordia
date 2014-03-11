#include "concordia/anubis_search_result.hpp"


AnubisSearchResult::AnubisSearchResult(
                const SUFFIX_MARKER_TYPE & exampleId, const double score):
                _exampleId(exampleId),
                _score(score) {
}

AnubisSearchResult::~AnubisSearchResult() {
}

