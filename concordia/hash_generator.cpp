#include "concordia/hash_generator.hpp"
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>

HashGenerator::HashGenerator(const string & wordMapFilePath)
                                         throw(ConcordiaException) :
    _wordMapFilePath(wordMapFilePath),
    _wordMap(boost::shared_ptr<WordMap>(new WordMap)) {
    if (boost::filesystem::exists(_wordMapFilePath)) {
        ifstream ifs(_wordMapFilePath.c_str(), std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        boost::shared_ptr<WordMap> restoredWordMap(new WordMap);
        ia >> *_wordMap;
    }
}

HashGenerator::~HashGenerator() {
}

vector<INDEX_CHARACTER_TYPE> HashGenerator::generateHash(
                                        const string & sentence) {
    vector<INDEX_CHARACTER_TYPE> result;
    vector<string> tokenTexts;
    boost::split(tokenTexts, sentence, boost::is_any_of(" "));

    for (vector<string>::iterator it = tokenTexts.begin();
                                it != tokenTexts.end(); ++it) {
        string token = *it;
        INDEX_CHARACTER_TYPE code = _wordMap->getWordCode(token);
        result.push_back(code);
    }

    return result;
}

void HashGenerator::serializeWordMap() {
    ofstream ofs(_wordMapFilePath.c_str(), std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << *_wordMap;
}


