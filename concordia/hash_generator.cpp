#include "concordia/hash_generator.hpp"
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <fstream>


HashGenerator::HashGenerator(const string & wordMapFilename) throw(ConcordiaException) {
    _wordMapFilename = wordMapFilename;
    if (boost::filesystem::exists(_wordMapFilename)) {
        ifstream ifs(_wordMapFilename.c_str(), std::ios::binary);
        boost::archive::binary_iarchive ia(ifs);
        ia >> _wordMap;
        
    }  
}

HashGenerator::~HashGenerator() {
}

vector<int> HashGenerator::generateHash(const string & sentence) {
    vector<int> result;
    return result;
}

void HashGenerator::serializeWordMap() {
    ofstream ofs(_wordMapFilename.c_str(), std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << _wordMap;
}


