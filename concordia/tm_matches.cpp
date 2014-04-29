#include "concordia/tm_matches.hpp"
#include <boost/foreach.hpp>
#include <math.h>

TmMatches::TmMatches(const SUFFIX_MARKER_TYPE exampleId,
                       const unsigned char exampleSize,
                       const unsigned char patternSize):
                        _exampleId(exampleId),
                        _exampleSize(exampleSize),
                        _patternSize(patternSize),
                        _score(0) {
}

TmMatches::~TmMatches() {
}

void TmMatches::calculateScore() {
    double exampleOverlay = _getLogarithmicOverlay(_exampleMatchedRegions,
                                                   _exampleSize, 1.0);

    double patternOverlay = _getLogarithmicOverlay(_patternMatchedRegions,
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
        _exampleMatchedRegions.push_back(new Interval(start, end));
    }
}

void TmMatches::addPatternInterval(int start, int end) {
    if (!_alreadyIntersects(_patternMatchedRegions, start, end)) {
        _patternMatchedRegions.push_back(new Interval(start, end));
    }
}

bool TmMatches::_alreadyIntersects(
                    boost::ptr_vector<Interval> intervalList,
                    int start, int end) {
    Interval * tempInterval = new Interval(start, end);
    BOOST_FOREACH(Interval & oldInterval, intervalList) {
        if (oldInterval.intersects(*tempInterval)) {
            delete tempInterval;
            return true;
        }
    }
    delete tempInterval;

    return false;
}

double TmMatches::_getLogarithmicOverlay(
                            boost::ptr_vector<Interval> intervalList,
                            unsigned char sentenceSize,
                            double k) {
    double overlayScore = 0;
    BOOST_FOREACH(Interval & interval, intervalList) {
        double intervalOverlay = static_cast<double>(interval.getLength())
                                 / static_cast<double>(sentenceSize);
        double significanceFactor = pow(log(interval.getLength()+1)
                                    / log(sentenceSize+1), 1/k);

        overlayScore += intervalOverlay * significanceFactor;
    }
    return overlayScore;
}

