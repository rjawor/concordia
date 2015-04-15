#include "concordia/example.hpp"
#include <climits>

Example::Example(const std::string & sentence, const SUFFIX_MARKER_TYPE & id)
                                              throw(ConcordiaException):
                                              _sentence(sentence),
                                              _id(id) {
    // check if the example id exceeds space
    // reserved for it in the suffix marker
    if (id >= SUFFIX_MARKER_TYPE_MAX_VALUE >> 8) {
        throw ConcordiaException("Example id too large.");
    }
}

Example::~Example() {
}

