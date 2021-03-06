#include <boost/filesystem.hpp>
#include "tests/unit-tests/unit_tests_globals.hpp"
#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>
#include "concordia/common/config.hpp"
#include "concordia/hash_generator.hpp"
#include "tests/common/test_resources_manager.hpp"

BOOST_AUTO_TEST_SUITE(hash_generator)

BOOST_AUTO_TEST_CASE( SimpleHashTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    
    if (boost::filesystem::exists(config->getWordMapFilePath())) {
        boost::filesystem::remove(config->getWordMapFilePath());      
    } 
    
    HashGenerator hashGenerator = HashGenerator(config);

    std::vector<INDEX_CHARACTER_TYPE> hash = hashGenerator.generateHash("Ala posiada kota");
    std::vector<INDEX_CHARACTER_TYPE> expected;
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(2);

    BOOST_CHECK_EQUAL_COLLECTIONS(hash.begin(), hash.end(), expected.begin(), expected.end());
}

/* Commentet out - the test takes too long. Run it once whenever the SUFFIX_MARKER_SENTENCE_BYTES parameter changes.
                   Or don't run it at all, whatever! I don't care! There is still the test for max sentence size in test_utils.cpp
BOOST_AUTO_TEST_CASE( TooLongHashTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    
    if (boost::filesystem::exists(config->getWordMapFilePath())) {
        boost::filesystem::remove(config->getWordMapFilePath());      
    } 
    
    HashGenerator hashGenerator = HashGenerator(config);

    std::stringstream ss;
    for (int i=0;i<65537;i++) {
        ss << "xx" << i << " ";
    }

    std::string longSentence = ss.str();
    
    bool exceptionThrown = false;
    std::string message = "";
    try {
        boost::shared_ptr<std::vector<INDEX_CHARACTER_TYPE> > hash = hashGenerator.generateHash(longSentence);
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Trying to add too long sentence"), true);    

    
}
*/

BOOST_AUTO_TEST_CASE( HashSerializationTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    
    if (boost::filesystem::exists(config->getWordMapFilePath())) {
        boost::filesystem::remove(config->getWordMapFilePath());      
    } 
    
    HashGenerator hashGenerator1 = HashGenerator(config);

    std::vector<INDEX_CHARACTER_TYPE> hash1 = hashGenerator1.generateHash("Ala posiada kota");
    std::vector<INDEX_CHARACTER_TYPE> expected1;
    expected1.push_back(0);
    expected1.push_back(1);
    expected1.push_back(2);
    BOOST_CHECK_EQUAL_COLLECTIONS(hash1.begin(), hash1.end(), expected1.begin(), expected1.end());

    hashGenerator1.serializeWordMap();
   
    HashGenerator hashGenerator2 = HashGenerator(config);
    std::vector<INDEX_CHARACTER_TYPE> hash2 = hashGenerator2.generateHash("Ala posiada psa");
    std::vector<INDEX_CHARACTER_TYPE> expected2;
    expected2.push_back(0);
    expected2.push_back(1);
    expected2.push_back(3);
    BOOST_CHECK_EQUAL_COLLECTIONS(hash2.begin(), hash2.end(), expected2.begin(), expected2.end());

    boost::filesystem::remove(config->getWordMapFilePath());       
}

BOOST_AUTO_TEST_CASE( TokenVectorTest )
{
    boost::shared_ptr<ConcordiaConfig> config(new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    
    if (boost::filesystem::exists(config->getWordMapFilePath())) {
        boost::filesystem::remove(config->getWordMapFilePath());      
    } 
    
    HashGenerator hashGenerator = HashGenerator(config);

    std::vector<std::string> tokenVector = hashGenerator.generateTokenVector("12.02.2014   o  godzinie 17:40 doszło do kolizji na ulicy Grobla; policjanci ustalili, że kierowca zaparkował  samochód.");
    std::vector<std::string> expected;
    expected.push_back("ne_date");
    expected.push_back("o");
    expected.push_back("godzinie");
    expected.push_back("ne_number");
    expected.push_back("ne_number");
    expected.push_back("doszło");
    expected.push_back("do");
    expected.push_back("kolizji");
    expected.push_back("na");
    expected.push_back("ulicy");
    expected.push_back("grobla");
    expected.push_back("policjanci");
    expected.push_back("ustalili");
    expected.push_back("że");
    expected.push_back("kierowca");
    expected.push_back("zaparkował");
    expected.push_back("samochód");

    BOOST_CHECK_EQUAL_COLLECTIONS(tokenVector.begin(), tokenVector.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
