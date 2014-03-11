#include "concordia/interval.hpp"


Interval::Interval(const unsigned char start, const unsigned char end):
                                                _start(start),
                                                _end(end) {
}

Interval::~Interval() {
}

bool Interval::intersects(Interval & interval) {
	return !(_end - 1 < interval.getStart() ||
	         interval.getEnd() - 1  < _start);
}

unsigned char Interval::getLength() {
    return _end - _start;
}

