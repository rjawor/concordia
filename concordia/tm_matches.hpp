#ifndef TM_MATCHES_HDR
#define TM_MATCHES_HDR

#include <string>
#include <vector>
#include <map>
#include "concordia/common/config.hpp"
#include "concordia/interval.hpp"
#include <boost/ptr_container/ptr_map.hpp>


/*!
  Class used within Anubis search algorithm to store partial results.

*/

using namespace std;

class TmMatches {
public:
    TmMatches();
        
    TmMatches(const SUFFIX_MARKER_TYPE exampleId,
              const SUFFIX_MARKER_TYPE exampleSize,
              const SUFFIX_MARKER_TYPE patternSize);

    /*! Destructor.
    */
    virtual ~TmMatches();

    double getScore() const {
        return _score;
    }

    vector<Interval> getExampleIntervals() const {
        return _exampleMatchedRegions;
    }

    vector<Interval> getPatternIntervals() const {
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
    bool _alreadyIntersects(const vector<Interval> & intervalList,
                            int start, int end);

    double _getLogarithmicOverlay(const vector<Interval> & intervalList,
                                  SUFFIX_MARKER_TYPE sentenceSize,
                                  double k);

    SUFFIX_MARKER_TYPE _exampleId;

    vector<Interval> _exampleMatchedRegions;

    vector<Interval> _patternMatchedRegions;

    SUFFIX_MARKER_TYPE _patternSize;

    SUFFIX_MARKER_TYPE _exampleSize;

    double _score;
};

typedef boost::ptr_map<SUFFIX_MARKER_TYPE, TmMatches> TmMatchesMap;
typedef TmMatchesMap::iterator TmMatchesMapIterator;

#endif
