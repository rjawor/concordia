#ifndef CONCORDIA_SEARCH_RESULT_HDR
#define CONCORDIA_SEARCH_RESULT_HDR

#include "concordia/common/config.hpp"
#include "concordia/matched_pattern_fragment.hpp"

#include <vector>
#include <string>

/*!
  Class representing result of concordia search.

*/

class ConcordiaSearchResult {
public:
    explicit ConcordiaSearchResult(
                const std::vector<std::string> & tokenVector);

    /*! Destructor.
    */
    virtual ~ConcordiaSearchResult();

    void addFragment(const MatchedPatternFragment & fragment);

    void sortFragments();

    void computeBestOverlay(SUFFIX_MARKER_TYPE patternSize);

    std::vector<std::string> getTokenVector() const {
        return _tokenVector;
    }

    std::vector<MatchedPatternFragment> getFragments() const {
        return _matchedPatternFragments;
    }

    std::vector<MatchedPatternFragment> getBestOverlay() const {
        return _bestOverlay;
    }

private:
    void _checkPossibleOverlays(
                std::vector<MatchedPatternFragment> currentOverlay,
                SUFFIX_MARKER_TYPE lastAddedPos,
                SUFFIX_MARKER_TYPE patternSize);

    std::vector<std::string> _tokenVector;

    std::vector<MatchedPatternFragment> _matchedPatternFragments;

    std::vector<MatchedPatternFragment> _bestOverlay;

    double _bestOverlayScore;
};

#endif
