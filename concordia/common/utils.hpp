#ifndef UTILS_HDR
#define UTILS_HDR

#include <boost/shared_ptr.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"
#include "build/libdivsufsort/include/divsufsort.h"

using namespace std;

class Utils {
public:
    explicit Utils();

    /*! Destructor.
    */
    virtual ~Utils();

    static void writeIndexCharacter(ofstream & file,
                                     INDEX_CHARACTER_TYPE character);

    static INDEX_CHARACTER_TYPE readIndexCharacter(ifstream & file);

    static sauchar_t * indexVectorToSaucharArray(
                       boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > input);

    static void appendCharToSaucharVector(
                             boost::shared_ptr<std::vector<sauchar_t> > vector,
                             INDEX_CHARACTER_TYPE character);
private:
    static void _insertCharToSaucharArray(sauchar_t * array,
                                 INDEX_CHARACTER_TYPE character, int pos);
};

#endif
