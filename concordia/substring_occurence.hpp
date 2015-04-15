#ifndef SUBSTRING_OCCURENCE_HDR
#define SUBSTRING_OCCURENCE_HDR

#include "concordia/common/config.hpp"
#include <string>

/*!
  Class representing occurence of a searched substring.

*/

class SubstringOccurence {
public:
    SubstringOccurence();

    explicit SubstringOccurence(const SUFFIX_MARKER_TYPE & marker);

    SubstringOccurence(const SUFFIX_MARKER_TYPE & id,
                                const SUFFIX_MARKER_TYPE & offset,
                                const SUFFIX_MARKER_TYPE & exampleLength);
    /*! Destructor.
    */
    virtual ~SubstringOccurence();

    SUFFIX_MARKER_TYPE getId() const {
        return _id;
    }

    SUFFIX_MARKER_TYPE getOffset() const {
        return _offset;
    }

    SUFFIX_MARKER_TYPE getExampleLength() const {
        return _exampleLength;
    }

    void enterDataFromMarker(const SUFFIX_MARKER_TYPE & marker);

private:
    SUFFIX_MARKER_TYPE _id;

    SUFFIX_MARKER_TYPE _offset;

    // the example
    SUFFIX_MARKER_TYPE _exampleLength;
};

#endif
