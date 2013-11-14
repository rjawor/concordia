#ifndef HASH_GENERATOR_HDR
#define HASH_GENERATOR_HDR

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "concordia/word_map.hpp"
#include "concordia/concordia_exception.hpp"

/*!
  Class for generating a sentence hash.

*/

using namespace std;

class HashGenerator {
public:
    explicit HashGenerator(const string & wordMapFilename)
                                    throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~HashGenerator();

    vector<int> generateHash(const string & sentence);

    void serializeWordMap();

private:
    boost::shared_ptr<WordMap> _wordMap;

    string _wordMapFilename;
};

#endif
