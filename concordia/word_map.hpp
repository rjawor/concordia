#ifndef WORD_MAP_HDR
#define WORD_MAP_HDR

#include <string>
#include <map>
#include "concordia/concordia_exception.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

#include "build/libdivsufsort/include/divsufsort.h"



/*!
  Class representing dictionary for word to int encoding.

*/

using namespace std;

class WordMap {
public:
    explicit WordMap() throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~WordMap();

    sauchar_t getWordCode(const string & word);

private:
    friend class boost::serialization::access;

    template<class Archive>

    void serialize(Archive & ar, const unsigned int version) {
        ar & _map;
        ar & _nextFree;
    }

    map<string, sauchar_t> _map;

    sauchar_t _nextFree;
};

#endif
