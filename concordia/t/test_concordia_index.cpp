#include "tests/unit-tests/unit_tests_globals.hpp"

#include "concordia/concordia_index.hpp"
#include "concordia/concordia_exception.hpp"
#include "tests/common/test_resources_manager.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(concordia_index)


BOOST_AUTO_TEST_CASE( ResourcesExistenceTest1 )
{
    bool exceptionThrown = false;
    string message = "";

    try {
        ConcordiaIndex index(TestResourcesManager::getTestFilePath("concordia-index","mock_word_map.bin"),
                             TestResourcesManager::getTestFilePath("concordia-index","nonexistent.bin"),
                             TestResourcesManager::getTestFilePath("concordia-index","test_SA.bin"));
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }
    
    BOOST_CHECK(exceptionThrown);
    BOOST_CHECK_EQUAL(boost::starts_with(message, "E01"), true);    
}

BOOST_AUTO_TEST_CASE( ResourcesExistenceTest2 )
{
    bool exceptionThrown = false;
    string message = "";

    try {
        ConcordiaIndex index(TestResourcesManager::getTestFilePath("concordia-index","nonexistent.bin"),
                             TestResourcesManager::getTestFilePath("concordia-index","mock_hash_index.bin"),
                             TestResourcesManager::getTestFilePath("concordia-index","test_SA.bin"));
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }
    
    BOOST_CHECK(exceptionThrown);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "E02"), true);    
}

BOOST_AUTO_TEST_CASE( SuffixArrayGenerationTest )
{
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_word_map.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_SA.bin"));
    index.addSentence("Ala ma kota");
    index.addSentence("Ala ma rysia");
    index.addSentence("Marysia ma rysia");

    index.generateSuffixArray();
                         
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_word_map.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_SA.bin")));
    
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_word_map.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_SA.bin"));
}

BOOST_AUTO_TEST_SUITE_END()
