#include "tests/unit-tests/unit_tests_globals.hpp"

#include "concordia/index_searcher.hpp"
#include "concordia/concordia_index.hpp"
#include "concordia/concordia_exception.hpp"
#include "tests/common/test_resources_manager.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(index_searcher)


BOOST_AUTO_TEST_CASE( SimpleSearchTest )
{

ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_word_map.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_SA.bin"));
    index.addSentence("Ala ma kota");
    index.addSentence("Ala ma rysia");
    index.addSentence("Marysia ma rysia");

    index.generateSuffixArray();
    index.serializeWordMap();
                         
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_word_map.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin")));
    BOOST_CHECK(boost::filesystem::exists(TestResourcesManager::getTestFilePath("temp","test_SA.bin")));
    
    IndexSearcher searcher;
    searcher.loadIndex(TestResourcesManager::getTestFilePath("temp","test_word_map.bin"),
                       TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                       TestResourcesManager::getTestFilePath("temp","test_SA.bin"));

    /*The test index contains 3 sentences:    
    "Ala ma kota"
    "Ala ma rysia"
    "Marysia ma rysia"
    
    Test word map:
    Ala -> 0
    ma -> 1
    kota -> 2
    rysia -> 3
    Marysia -> 4
    
    Test hashed index:
       n: 0 1 2 3 4 5 6 7 8
    T[n]: 0 1 2 0 1 3 4 1 3 
    
    Test suffix array:
        n: 0 1 2 3 4 5 6 7 8
    SA[n]: 0 3 1 7 4 2 8 5 6
    
    */
    
    vector<saidx_t> expectedResult1;
    expectedResult1.push_back(7);
    expectedResult1.push_back(4);
    
    vector<saidx_t> searchResult1 = searcher.simpleSearch("ma rysia");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_word_map.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin")); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp","test_SA.bin"));                                 

    BOOST_CHECK_EQUAL_COLLECTIONS(searchResult1.begin(), searchResult1.end(), 
                                 expectedResult1.begin(), expectedResult1.end());
                                 
                          
}

BOOST_AUTO_TEST_SUITE_END()
