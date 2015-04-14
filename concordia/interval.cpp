#include "concordia/interval.hpp"


Interval::Interval(const SUFFIX_MARKER_TYPE start, const SUFFIX_MARKER_TYPE end):
                                                _start(start),
                                                _end(end) {
}

Interval::~Interval() {
}

bool Interval::intersects(Interval & interval) {
    return !(_end - 1 < interval.getStart() ||
             interval.getEnd() - 1  < _start);
}

SUFFIX_MARKER_TYPE Interval::getLength() {
    return _end - _start;
}

