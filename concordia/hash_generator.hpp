#ifndef HASH_GENERATOR_HDR
#define HASH_GENERATOR_HDR

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "concordia/word_map.hpp"
#include "concordia/concordia_exception.hpp"

#include <divsufsort.h>


/*!
  Class for generating a sentence hash.

*/

using namespace std;

class HashGenerator {
public:
    explicit HashGenerator(const string & wordMapFilePath)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~HashGenerator();

    vector<sauchar_t> generateHash(const string & sentence);

    void serializeWordMap();

private:
    boost::shared_ptr<WordMap> _wordMap;

    string _wordMapFilePath;
};

#endif
