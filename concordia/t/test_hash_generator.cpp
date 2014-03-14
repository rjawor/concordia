#include <boost/filesystem.hpp>
#include "tests/unit-tests/unit_tests_globals.hpp"
#include <string>
#include <sstream>

#include "concordia/common/config.hpp"
#include "concordia/hash_generator.hpp"

#define TEST_WORD_MAP_PATH "/tmp/test_word_map.bin"

using namespace std;

BOOST_AUTO_TEST_SUITE(hash_generator)

BOOST_AUTO_TEST_CASE( SimpleHashTest )
{
    if (boost::filesystem::exists(TEST_WORD_MAP_PATH)) {
        boost::filesystem::remove(TEST_WORD_MAP_PATH);      
    } 
    
    HashGenerator hashGenerator = HashGenerator(TEST_WORD_MAP_PATH);

    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash = hashGenerator.generateHash("Ala ma kota");
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > expected(new vector<INDEX_CHARACTER_TYPE>());
    expected->push_back(0);
    expected->push_back(1);
    expected->push_back(2);

    BOOST_CHECK_EQUAL_COLLECTIONS(hash->begin(), hash->end(), expected->begin(), expected->end());
}

BOOST_AUTO_TEST_CASE( TooLongHashTest )
{
    if (boost::filesystem::exists(TEST_WORD_MAP_PATH)) {
        boost::filesystem::remove(TEST_WORD_MAP_PATH);      
    } 
    
    HashGenerator hashGenerator = HashGenerator(TEST_WORD_MAP_PATH);

    stringstream ss;
    for (int i=0;i<256;i++) {
        ss << "a" << i << " ";
    }

    string longSentence = ss.str();
    
    bool exceptionThrown = false;
    string message = "";
    try {
        boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash = hashGenerator.generateHash(longSentence);
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Trying to add to long sentence"), true);    

    
}

BOOST_AUTO_TEST_CASE( HashSerializationTest )
{
    if (boost::filesystem::exists(TEST_WORD_MAP_PATH)) {
        boost::filesystem::remove(TEST_WORD_MAP_PATH);      
    } 

    HashGenerator hashGenerator1 = HashGenerator(TEST_WORD_MAP_PATH);
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash1 = hashGenerator1.generateHash("Ala ma kota");
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > expected1(new vector<INDEX_CHARACTER_TYPE>());
    expected1->push_back(0);
    expected1->push_back(1);
    expected1->push_back(2);
    BOOST_CHECK_EQUAL_COLLECTIONS(hash1->begin(), hash1->end(), expected1->begin(), expected1->end());

    hashGenerator1.serializeWordMap();
   
    HashGenerator hashGenerator2 = HashGenerator(TEST_WORD_MAP_PATH);
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > hash2 = hashGenerator2.generateHash("Ala ma psa");
    boost::shared_ptr<vector<INDEX_CHARACTER_TYPE> > expected2(new vector<INDEX_CHARACTER_TYPE>());
    expected2->push_back(0);
    expected2->push_back(1);
    expected2->push_back(3);
    BOOST_CHECK_EQUAL_COLLECTIONS(hash2->begin(), hash2->end(), expected2->begin(), expected2->end());

    boost::filesystem::remove(TEST_WORD_MAP_PATH);       
}

BOOST_AUTO_TEST_SUITE_END()
