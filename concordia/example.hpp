#ifndef EXAMPLE_HDR
#define EXAMPLE_HDR

#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include <string>

/*!
  Class representing a single sentence to be added into index along with its id.

*/

using namespace std;

class Example {
public:
    explicit Example(const string & sentence, const SUFFIX_MARKER_TYPE & id) throw (ConcordiaException);

    /*! Destructor.
    */
    virtual ~Example();

    string getSentence() const {
        return _sentence;
    }

    SUFFIX_MARKER_TYPE getId() const {
        return _id;
    }

private:
    string _sentence;

    SUFFIX_MARKER_TYPE _id;
};

#endif
