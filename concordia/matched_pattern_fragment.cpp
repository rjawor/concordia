#include "concordia/matched_pattern_fragment.hpp"

MatchedPatternFragment::MatchedPatternFragment(
                                   const SUFFIX_MARKER_TYPE & exampleId,
                                   const SUFFIX_MARKER_TYPE & exampleOffset,
                                   const SUFFIX_MARKER_TYPE & patternOffset,
                                   const SUFFIX_MARKER_TYPE & matchedLength):
                                   _exampleId(exampleId),
                                   _exampleOffset(exampleOffset),
                                   _patternOffset(patternOffset),
                                   _matchedLength(matchedLength) {
}

MatchedPatternFragment::~MatchedPatternFragment() {
}

