#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/concordia.hpp"
#include "tests/common/test_resources_manager.hpp"
#include "concordia/common/config.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(concordia_main)

BOOST_AUTO_TEST_CASE( ConcordiaVersion )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    string version = concordia.getVersion();
    BOOST_CHECK_EQUAL( version , "0.1");
}

BOOST_AUTO_TEST_CASE( ConcordiaSimpleSearch1 )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    concordia.addSentence("Ala ma kota");
    concordia.addSentence("Ala ma rysia");
    concordia.addSentence("Marysia ma rysia");
    concordia.refreshSAfromRAM();
        
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
    
    boost::shared_ptr<std::vector<saidx_t> > expectedResult1(new std::vector<saidx_t>());
    expectedResult1->push_back(7);
    expectedResult1->push_back(4);
    
    boost::shared_ptr<std::vector<saidx_t> > searchResult1 = concordia.simpleSearch("ma rysia");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    BOOST_CHECK_EQUAL_COLLECTIONS(searchResult1->begin(), searchResult1->end(), 
                                 expectedResult1->begin(), expectedResult1->end());

}

BOOST_AUTO_TEST_CASE( ConcordiaSimpleSearch2 )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    boost::shared_ptr<vector<string> > testSentences (new vector<string>());
    testSentences->push_back("to jest okno");
    testSentences->push_back("czy jest okno otwarte");
    testSentences->push_back("chyba to jest tutaj");
    testSentences->push_back("to jest");
    concordia.addAllSentences(testSentences);

    /*The test index contains 4 sentences:    
    "to jest okno"
    "czy jest okno otwarte"
    "chyba to jest tutaj"
    "to jest"
    
    Test word map:
    to -> 0
    jest -> 1
    okno -> 2
    czy -> 3
    otwarte -> 4
    chyba -> 5
    tutaj -> 6
    
    Test hashed index:
        n:  0  1  2  3  4  5  6  7  8  9 10 11 12
     T[n]:  0  1  2  3  1  2  4  5  0  1  6  0  1
    
    Test suffix array:
        n:  0  1  2  3  4  5  6  7  8  9 10 11 12
    SA[n]: 11  0  8 12  1  4  9  2  5  3  6  7 10
    
    */
    
    boost::shared_ptr<vector<saidx_t> > expectedResult1(new vector<saidx_t>());
    expectedResult1->push_back(11);
    expectedResult1->push_back(0);
    expectedResult1->push_back(8);

    boost::shared_ptr<vector<saidx_t> > expectedResult2(new vector<saidx_t>());
    expectedResult2->push_back(1);
    expectedResult2->push_back(4);
    
    Concordia concordia2 = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    boost::shared_ptr<vector<saidx_t> > searchResult1 = concordia2.simpleSearch("to jest");
    boost::shared_ptr<vector<saidx_t> > searchResult2 = concordia2.simpleSearch("jest okno");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    BOOST_CHECK_EQUAL_COLLECTIONS(searchResult1->begin(), searchResult1->end(), 
                                 expectedResult1->begin(), expectedResult1->end());
    BOOST_CHECK_EQUAL_COLLECTIONS(searchResult2->begin(), searchResult2->end(), 
                                 expectedResult2->begin(), expectedResult2->end());

}

BOOST_AUTO_TEST_SUITE_END()
