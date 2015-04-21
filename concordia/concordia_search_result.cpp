#include "concordia/concordia_search_result.hpp"

#include "concordia/common/utils.hpp"
#include <algorithm>

ConcordiaSearchResult::ConcordiaSearchResult(
                        const std::vector<std::string> & tokenVector):
                                   _tokenVector(tokenVector),
                                   _bestOverlayScore(0) {
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

void ConcordiaSearchResult::computeBestOverlay(
                                     SUFFIX_MARKER_TYPE patternSize) {
    // the fragments are already sorted by their ends, ascending
    _checkPossibleOverlays(std::vector<MatchedPatternFragment>(),
                           -1,
                           patternSize);
}

void ConcordiaSearchResult::_checkPossibleOverlays(
            std::vector<MatchedPatternFragment> currentOverlay,
            SUFFIX_MARKER_TYPE lastAddedPos,
            SUFFIX_MARKER_TYPE patternSize) {
    bool allTerminal = true;
    for (int i = lastAddedPos + 1; i < _matchedPatternFragments.size(); i++) {
        MatchedPatternFragment fragment = _matchedPatternFragments.at(i);

        // if fragment does not intersect currentOverlay
        if (currentOverlay.size() == 0 ||
            !currentOverlay.at(currentOverlay.size()-1).intersects(fragment)) {
            currentOverlay.push_back(fragment);
            _checkPossibleOverlays(currentOverlay, i, patternSize);
            allTerminal = false;
        }
    }

    if (allTerminal) {
        double score = Utils::getLogarithmicOverlay(currentOverlay,
                                                    patternSize,
                                                    1.0);
        if (score > _bestOverlayScore) {
            _bestOverlay = currentOverlay;
            _bestOverlayScore = score;
        }
    }
}

