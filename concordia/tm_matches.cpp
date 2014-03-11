#include "concordia/tm_matches.hpp"
#include <boost/foreach.hpp>


TmMatches::TmMatches(const SUFFIX_MARKER_TYPE exampleId,
                       const unsigned char exampleSize,
                       const unsigned char patternSize):
                        _exampleId(exampleId),
                        _exampleSize(exampleSize),
                        _patternSize(patternSize) {
}

TmMatches::~TmMatches() {
}

void TmMatches::calculateScore() {
    /* TODO logarithmic function
	unsigned char exampleMatchedLength = 0;
	BOOST_FOREACH(Interval & interval, _exampleMatchedRegions) {
		exampleMatchedLength += interval.getLength();
	}

	unsigned char patternMatchedLength = 0;
	BOOST_FOREACH(Interval & interval, _patternMatchedRegions) {
		patternMatchedLength += interval.getLength();
	}

	_score = (double) (exampleMatchedLength + patternMatchedLength)
			/ (double) (_exampleSize + _patternSize);
    */
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

	_score = (double) (exampleMatchedLength + patternMatchedLength)
			/ (double) (_exampleSize + _patternSize);
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

