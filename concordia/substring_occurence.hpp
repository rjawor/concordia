#ifndef SUBSTRING_OCCURENCE_HDR
#define SUBSTRING_OCCURENCE_HDR

#include "concordia/common/config.hpp"
#include <string>

/*!
  Class representing occurence of a searched substring.

*/

using namespace std;

class SubstringOccurence {
public:
    explicit SubstringOccurence(const SUFFIX_MARKER_TYPE & id,
                                const int & offset);

    /*! Destructor.
    */
    virtual ~SubstringOccurence();

    SUFFIX_MARKER_TYPE getId() const {
        return _id;
    }

    int getOffset() const {
        return _offset;
    }

private:
    SUFFIX_MARKER_TYPE _id;

    int _offset;
};

#endif
