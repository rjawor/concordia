#ifndef UTILS_HDR
#define UTILS_HDR

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include "concordia/interval.hpp"
#include "concordia/matched_pattern_fragment.hpp"
#include <divsufsort.h>

class Utils {
public:
    explicit Utils();

    /*! Destructor.
    */
    virtual ~Utils();

    static void writeIndexCharacter(std::ofstream & file,
                                     INDEX_CHARACTER_TYPE character);

    static void writeMarker(std::ofstream & file,
                                     SUFFIX_MARKER_TYPE marker);

    static INDEX_CHARACTER_TYPE readIndexCharacter(std::ifstream & file);

    static SUFFIX_MARKER_TYPE readMarker(std::ifstream & file);

    static sauchar_t * indexVectorToSaucharArray(
                       const std::vector<INDEX_CHARACTER_TYPE> & input);

    static std::vector<sauchar_t> indexVectorToSaucharVector(
                       const std::vector<INDEX_CHARACTER_TYPE> & input);

    static void appendCharToSaucharVector(
                             boost::shared_ptr<std::vector<sauchar_t> > vector,
                             INDEX_CHARACTER_TYPE character);

    static void appendCharToSaucharVector(
                             std::vector<sauchar_t> & vector,
                             INDEX_CHARACTER_TYPE character);

    template <typename T>
    static void printVector(const std::vector<T> & vector);

    static SUFFIX_MARKER_TYPE getIdFromMarker(SUFFIX_MARKER_TYPE marker);

    static SUFFIX_MARKER_TYPE getOffsetFromMarker(SUFFIX_MARKER_TYPE marker);

    static SUFFIX_MARKER_TYPE getLengthFromMarker(SUFFIX_MARKER_TYPE marker);

    static SUFFIX_MARKER_TYPE createMarker(SUFFIX_MARKER_TYPE id,
                                           SUFFIX_MARKER_TYPE offset,
                                           SUFFIX_MARKER_TYPE length);

    static double getLogarithmicOverlay(
                                  const std::vector<Interval> & intervalList,
                                  SUFFIX_MARKER_TYPE sentenceSize,
                                  double k);

    static double getLogarithmicOverlay(
                      const std::vector<MatchedPatternFragment> & fragmentList,
                      SUFFIX_MARKER_TYPE patternSize,
                      double k);

    static SUFFIX_MARKER_TYPE maxSentenceSize;

private:
    static void _insertCharToSaucharArray(sauchar_t * array,
                                 INDEX_CHARACTER_TYPE character, int pos);

    static int _idBytes;
};

template <typename T>
void Utils::printVector(const std::vector<T> & vector) {
    for (int i = 0; i < vector.size(); i++) {
        std::cout << static_cast<int>(vector.at(i)) << " ";
    }
    std::cout << std::endl;
}
#endif
