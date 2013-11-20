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
    ConcordiaIndex index(TestResourcesManager::getTestWordMapFilePath("mock_word_map.bin"),
                         TestResourcesManager::getTestHashIndexFilePath("mock_hash_index.bin"),
                         TestResourcesManager::getTestSuffixArrayFilePath());
                         
}


BOOST_AUTO_TEST_CASE( ResourcesExistenceTest2 )
{
    bool exceptionThrown = false;
    string message = "";

    try {
        ConcordiaIndex index(TestResourcesManager::getTestWordMapFilePath("mock_word_map.bin"),
                             TestResourcesManager::getTestHashIndexFilePath("nonexistent.bin"),
                             TestResourcesManager::getTestSuffixArrayFilePath());
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }
    
    BOOST_CHECK(exceptionThrown);
    BOOST_CHECK_EQUAL(boost::starts_with(message, "E01"), true);    
}

BOOST_AUTO_TEST_CASE( ResourcesExistenceTest3 )
{
    bool exceptionThrown = false;
    string message = "";

    try {
        ConcordiaIndex index(TestResourcesManager::getTestWordMapFilePath("nonexistent.bin"),
                             TestResourcesManager::getTestHashIndexFilePath("mock_hash_index.bin"),
                             TestResourcesManager::getTestSuffixArrayFilePath());
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }
    
    BOOST_CHECK(exceptionThrown);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "E02"), true);    
}

BOOST_AUTO_TEST_CASE( SuffixArrayGenerationTest )
{
    ConcordiaIndex index(TestResourcesManager::getTestWordMapFilePath("test_word_map.bin"),
                         TestResourcesManager::getTestHashIndexFilePath("test_hash_index.bin"),
                         TestResourcesManager::getTestSuffixArrayFilePath());
    index.addSentence("Ala ma kota");
    index.generateSuffixArray();
    index.serializeWordMap();
                         
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestWordMapFilePath("test_word_map.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestHashIndexFilePath("test_hash_index.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestSuffixArrayFilePath()));
    
    boost::filesystem::remove(TestResourcesManager::getTestWordMapFilePath("test_word_map.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestHashIndexFilePath("test_hash_index.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestSuffixArrayFilePath()); 
}

BOOST_AUTO_TEST_SUITE_END()
