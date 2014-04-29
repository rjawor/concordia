#ifndef HASH_GENERATOR_HDR
#define HASH_GENERATOR_HDR

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "concordia/word_map.hpp"
#include "concordia/common/config.hpp"
#include "concordia/sentence_anonymizer.hpp"
#include "concordia/concordia_config.hpp"
#include "concordia/concordia_exception.hpp"


/*!
  Class for generating a sentence hash.

*/

using namespace std;

class HashGenerator {
public:
    explicit HashGenerator(boost::shared_ptr<ConcordiaConfig> config)
                                            throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~HashGenerator();

    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> >
                    generateHash(const string & sentence)
                                throw(ConcordiaException);

    boost::shared_ptr<vector<string> >
                    generateTokenVector(const string & sentence);

    void serializeWordMap();

private:
    boost::shared_ptr<WordMap> _wordMap;

    boost::shared_ptr<SentenceAnonymizer> _sentenceAnonymizer;

    string _wordMapFilePath;
};

#endif
