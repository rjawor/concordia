#ifndef TM_MATCHES_HDR
#define TM_MATCHES_HDR

#include <string>
#include "concordia/common/config.hpp"
#include "concordia/interval.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>


/*!
  Class used within Anubis search algorithm to store partial results.

*/

using namespace std;

class TmMatches {
public:
    explicit TmMatches(const SUFFIX_MARKER_TYPE exampleId,
                       const unsigned char exampleSize,
                       const unsigned char patternSize);

    /*! Destructor.
    */
    virtual ~TmMatches();

    double getScore() const {
        return _score;
    }

    boost::ptr_vector<Interval> getExampleIntervals() const {
        return _exampleMatchedRegions;
    }

    boost::ptr_vector<Interval> getPatternIntervals() const {
        return _patternMatchedRegions;
    }

    SUFFIX_MARKER_TYPE getExampleId() const {
        return _exampleId;
    }

    void calculateSimpleScore();

    void calculateScore();

    void addExampleInterval(int start, int end);

    void addPatternInterval(int start, int end);

private:
    bool _alreadyIntersects(boost::ptr_vector<Interval> intervalList,
                           int start, int end);

    double _getLogarithmicOverlay(boost::ptr_vector<Interval> intervalList,
                                 unsigned char sentenceSize,
                                 double k);

    SUFFIX_MARKER_TYPE _exampleId;

    boost::ptr_vector<Interval> _exampleMatchedRegions;

    boost::ptr_vector<Interval> _patternMatchedRegions;

    unsigned char _patternSize;

    unsigned char _exampleSize;

    double _score;
};

typedef boost::ptr_map<SUFFIX_MARKER_TYPE, TmMatches> TmMatchesMap;
typedef TmMatchesMap::iterator TmMatchesMapIterator;

#endif
