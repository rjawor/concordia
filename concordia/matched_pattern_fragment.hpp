#ifndef MATCHED_PATTERN_FRAGMENT_HDR
#define MATCHED_PATTERN_FRAGMENT_HDR

#include "concordia/common/config.hpp"

/*!
  Class representing matched pattern fragment in concordia search.

*/

class MatchedPatternFragment {
public:
    MatchedPatternFragment(const SUFFIX_MARKER_TYPE & exampleId,
                           const SUFFIX_MARKER_TYPE & exampleOffset,
                           const SUFFIX_MARKER_TYPE & patternOffset,
                           const SUFFIX_MARKER_TYPE & matchedLength);
    /*! Destructor.
    */
    virtual ~MatchedPatternFragment();

    SUFFIX_MARKER_TYPE getExampleId() const {
        return _exampleId;
    }

    SUFFIX_MARKER_TYPE getExampleOffset() const {
        return _exampleOffset;
    }

    SUFFIX_MARKER_TYPE getPatternOffset() const {
        return _patternOffset;
    }

    SUFFIX_MARKER_TYPE getMatchedLength() const {
        return _matchedLength;
    }

    bool operator > (const MatchedPatternFragment & other) const {
        return (_matchedLength > other.getMatchedLength());
    }

private:
    SUFFIX_MARKER_TYPE _exampleId;

    SUFFIX_MARKER_TYPE _exampleOffset;

    SUFFIX_MARKER_TYPE _patternOffset;

    SUFFIX_MARKER_TYPE _matchedLength;
};

#endif
