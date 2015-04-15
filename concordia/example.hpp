#ifndef EXAMPLE_HDR
#define EXAMPLE_HDR

#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include <string>

/*!
  Class representing a single sentence to be added into index along with its id.

*/

class Example {
public:
    explicit Example(const std::string & sentence,
                     const SUFFIX_MARKER_TYPE & id)
                                           throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~Example();

    std::string getSentence() const {
        return _sentence;
    }

    SUFFIX_MARKER_TYPE getId() const {
        return _id;
    }

private:
    std::string _sentence;

    SUFFIX_MARKER_TYPE _id;
};

#endif
