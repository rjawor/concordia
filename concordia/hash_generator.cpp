#include "concordia/hash_generator.hpp"
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
        ifstream ifs(_wordMapFilePath.c_str(), std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        boost::shared_ptr<WordMap> restoredWordMap(new WordMap);
        ia >> *_wordMap;
    }
}

HashGenerator::~HashGenerator() {
}

boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > HashGenerator::generateHash(
                         const string & sentence) throw(ConcordiaException) {
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> >
                                  result(new vector<INDEX_CHARACTER_TYPE>());
    boost::shared_ptr<vector<string> > tokenTexts =
                        generateTokenVector(sentence);
    if (tokenTexts->size() > MAX_SENTENCE_SIZE) {
        throw ConcordiaException("Trying to add too long sentence.");
    }
    for (vector<string>::iterator it = tokenTexts->begin();
                                it != tokenTexts->end(); ++it) {
        string token = *it;
        INDEX_CHARACTER_TYPE code = _wordMap->getWordCode(token);
        result->push_back(code);
    }

    return result;
}

boost::shared_ptr<vector<string> >
                  HashGenerator::generateTokenVector(const string & sentence) {
    string anonymizedSentence = _sentenceAnonymizer->anonymize(sentence);
    boost::shared_ptr<vector<string> > tokenTexts(new vector<string>());
    boost::split(*tokenTexts, anonymizedSentence, boost::is_any_of(" \t\r\n"),
                 boost::algorithm::token_compress_on);

    return tokenTexts;
}


void HashGenerator::serializeWordMap() {
    ofstream ofs(_wordMapFilePath.c_str(), std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << *_wordMap;
}


