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
                                vector<INDEX_CHARACTER_TYPE> & input);

    static void insertCharToSaucharArray(sauchar_t * array,
                             INDEX_CHARACTER_TYPE character, int pos);
private:
};

#endif
