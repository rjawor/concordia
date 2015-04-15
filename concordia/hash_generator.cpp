#include "concordia/hash_generator.hpp"
#include "concordia/common/utils.hpp"

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/algorithm/string.hpp>

#include <fstream>

HashGenerator::HashGenerator(boost::shared_ptr<ConcordiaConfig> config)
                                         throw(ConcordiaException) :
    _wordMapFilePath(config->getWordMapFilePath()),
    _wordMap(boost::shared_ptr<WordMap>(new WordMap)),
    _sentenceAnonymizer(boost::shared_ptr<SentenceAnonymizer>(
                                    new SentenceAnonymizer(config))) {
    if (boost::filesystem::exists(_wordMapFilePath)) {
        std::ifstream ifs(_wordMapFilePath.c_str(), std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        boost::shared_ptr<WordMap> restoredWordMap(new WordMap);
        ia >> *_wordMap;
    }
}

HashGenerator::~HashGenerator() {
}

std::vector<INDEX_CHARACTER_TYPE> HashGenerator::generateHash(
                     const std::string & sentence) throw(ConcordiaException) {
    std::vector<INDEX_CHARACTER_TYPE> result;
    std::vector<std::string> tokenTexts = generateTokenVector(sentence);
    if (tokenTexts.size() > Utils::maxSentenceSize) {
        throw ConcordiaException("Trying to add too long sentence.");
    }
    for (std::vector<std::string>::iterator it = tokenTexts.begin();
                                it != tokenTexts.end(); ++it) {
        std::string token = *it;
        INDEX_CHARACTER_TYPE code = _wordMap->getWordCode(token);
        result.push_back(code);
    }

    return result;
}

std::vector<std::string> HashGenerator::generateTokenVector(
                                               const std::string & sentence) {
    std::string anonymizedSentence = _sentenceAnonymizer->anonymize(sentence);
    boost::trim(anonymizedSentence);
    std::vector<std::string> tokenTexts;
    boost::split(tokenTexts, anonymizedSentence, boost::is_any_of(" \t\r\n"),
                 boost::algorithm::token_compress_on);
    return tokenTexts;
}


void HashGenerator::serializeWordMap() {
    std::ofstream ofs(_wordMapFilePath.c_str(), std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << *_wordMap;
}


