#ifndef ANUBIS_SEARCH_RESULT_HDR
#define ANUBIS_SEARCH_RESULT_HDR

#include "concordia/common/config.hpp"

/*!
  Class representing an example found by anubis search.

*/

class AnubisSearchResult {
public:
    explicit AnubisSearchResult(const SUFFIX_MARKER_TYPE & exampleId,
                                const double score);

    /*! Destructor.
    */
    virtual ~AnubisSearchResult();

    SUFFIX_MARKER_TYPE getExampleId() const {
        return _exampleId;
    }

    double getScore() const {
        return _score;
    }

    bool operator > (const AnubisSearchResult & other) const {
        return (_score > other.getScore());
    }
private:
    SUFFIX_MARKER_TYPE _exampleId;

    double _score;
};

#endif
