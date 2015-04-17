#ifndef CONCORDIA_SEARCH_RESULT_HDR
#define CONCORDIA_SEARCH_RESULT_HDR

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

    std::vector<std::string> getTokenVector() const {
        return _tokenVector;
    }

    std::vector<MatchedPatternFragment> getFragments() const {
        return _matchedPatternFragments;
    }

private:
    std::vector<std::string> _tokenVector;

    std::vector<MatchedPatternFragment> _matchedPatternFragments;
};

#endif
