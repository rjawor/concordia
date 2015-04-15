#ifndef INTERVAL_HDR
#define INTERVAL_HDR

#include "concordia/common/config.hpp"

/*!
  Class representing word interval.

*/

class Interval {
public:
    explicit Interval(const SUFFIX_MARKER_TYPE start,
                      const SUFFIX_MARKER_TYPE end);

    /*! Destructor.
    */
    virtual ~Interval();

    bool intersects(Interval & interval);

    SUFFIX_MARKER_TYPE getLength();

    SUFFIX_MARKER_TYPE getStart() const {
        return _start;
    }

    SUFFIX_MARKER_TYPE getEnd() const {
        return _end;
    }

private:
    SUFFIX_MARKER_TYPE _start;

    SUFFIX_MARKER_TYPE _end;
};

#endif
