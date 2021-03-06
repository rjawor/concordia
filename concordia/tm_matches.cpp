#include "concordia/tm_matches.hpp"

#include "concordia/common/utils.hpp"
#include <boost/foreach.hpp>
#include <math.h>

TmMatches::TmMatches() {
}

TmMatches::TmMatches(const SUFFIX_MARKER_TYPE exampleId,
                     const SUFFIX_MARKER_TYPE exampleSize,
                     const SUFFIX_MARKER_TYPE patternSize):
                      _exampleId(exampleId),
                      _exampleSize(exampleSize),
                      _patternSize(patternSize),
                      _score(0) {
}

TmMatches::~TmMatches() {
}

void TmMatches::calculateScore() {
    double exampleOverlay =
                  Utils::getLogarithmicOverlay(_exampleMatchedRegions,
                                                   _exampleSize, 1.0);

    double patternOverlay =
                  Utils::getLogarithmicOverlay(_patternMatchedRegions,
                                                   _patternSize, 2.0);
    _score = (exampleOverlay + patternOverlay) / 2.0;
}

void TmMatches::calculateSimpleScore() {
    unsigned char exampleMatchedLength = 0;
    BOOST_FOREACH(Interval & interval, _exampleMatchedRegions) {
        exampleMatchedLength += interval.getLength();
    }

    unsigned char patternMatchedLength = 0;
    BOOST_FOREACH(Interval & interval, _patternMatchedRegions) {
        patternMatchedLength += interval.getLength();
    }

    _score = static_cast<double>(exampleMatchedLength + patternMatchedLength)
             / static_cast<double>(_exampleSize + _patternSize);
}

void TmMatches::addExampleInterval(int start, int end) {
    if (!_alreadyIntersects(_exampleMatchedRegions, start, end)) {
        _exampleMatchedRegions.push_back(Interval(start, end));
    }
}

void TmMatches::addPatternInterval(int start, int end) {
    if (!_alreadyIntersects(_patternMatchedRegions, start, end)) {
        _patternMatchedRegions.push_back(Interval(start, end));
    }
}

bool TmMatches::_alreadyIntersects(
                    const std::vector<Interval> & intervalList,
                    int start, int end) {
    Interval tempInterval(start, end);
    BOOST_FOREACH(Interval oldInterval, intervalList) {
        if (oldInterval.intersects(tempInterval)) {
            return true;
        }
    }
    return false;
}
