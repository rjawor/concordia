#ifndef HASH_GENERATOR_HDR
#define HASH_GENERATOR_HDR

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "concordia/word_map.hpp"
#include "concordia/common/config.hpp"
#include "concordia/concordia_exception.hpp"


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

    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> >
                    generateHash(const string & sentence)
                                throw(ConcordiaException);

    void serializeWordMap();

private:
    boost::shared_ptr<WordMap> _wordMap;

    string _wordMapFilePath;
};

#endif
