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

class HashGenerator {
public:
    explicit HashGenerator(boost::shared_ptr<ConcordiaConfig> config)
                                            throw(ConcordiaException);

    /*! Destructor.
    */
    virtual ~HashGenerator();

    std::vector<INDEX_CHARACTER_TYPE> generateHash(const std::string & sentence)
                                throw(ConcordiaException);

    std::vector<std::string> generateTokenVector(const std::string & sentence);

    void serializeWordMap();

private:
    boost::shared_ptr<WordMap> _wordMap;

    boost::shared_ptr<SentenceAnonymizer> _sentenceAnonymizer;

    std::string _wordMapFilePath;
};

#endif
