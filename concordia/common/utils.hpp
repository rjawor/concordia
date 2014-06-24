#ifndef UTILS_HDR
#define UTILS_HDR

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include <divsufsort.h>

using namespace std;

class Utils {
public:
    explicit Utils();

    /*! Destructor.
    */
    virtual ~Utils();

    static void writeIndexCharacter(ofstream & file,
                                     INDEX_CHARACTER_TYPE character);

    static void writeMarker(ofstream & file,
                                     SUFFIX_MARKER_TYPE marker);

    static INDEX_CHARACTER_TYPE readIndexCharacter(ifstream & file);

    static SUFFIX_MARKER_TYPE readMarker(ifstream & file);

    static sauchar_t * indexVectorToSaucharArray(
                       boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > input);

    static boost::shared_ptr<std::vector<sauchar_t> >
                   indexVectorToSaucharVector(
                       boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > input);

    static void appendCharToSaucharVector(
                             boost::shared_ptr<std::vector<sauchar_t> > vector,
                             INDEX_CHARACTER_TYPE character);

    template <typename T>
    static void printVector(boost::shared_ptr<std::vector<T> > vector);

private:
    static void _insertCharToSaucharArray(sauchar_t * array,
                                 INDEX_CHARACTER_TYPE character, int pos);
};

template <typename T>
void Utils::printVector(boost::shared_ptr<std::vector<T> > vector) {
    for (int i = 0; i < vector->size(); i++) {
        cout << vector->at(i) << " ";
    }
    cout << endl;
}
#endif
