#include "concordia/concordia_search_result.hpp"

#include <algorithm>

ConcordiaSearchResult::ConcordiaSearchResult(
                        const std::vector<std::string> & tokenVector):
                                   _tokenVector(tokenVector) {
}

ConcordiaSearchResult::~ConcordiaSearchResult() {
}

void ConcordiaSearchResult::addFragment(
                    const MatchedPatternFragment & fragment) {
    _matchedPatternFragments.push_back(fragment);
}

void ConcordiaSearchResult::sortFragments() {
    std::sort(_matchedPatternFragments.begin(),
              _matchedPatternFragments.end(),
              std::greater<MatchedPatternFragment>());
}
