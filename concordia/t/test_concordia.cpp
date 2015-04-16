#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/concordia.hpp"
#include "concordia/anubis_search_result.hpp"
#include "tests/common/test_resources_manager.hpp"
#include "concordia/common/config.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <string>

BOOST_AUTO_TEST_SUITE(concordia_main)

BOOST_AUTO_TEST_CASE( ConcordiaVersion )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    std::string version = concordia.getVersion();
    BOOST_CHECK_EQUAL( version , "0.1");
}


BOOST_AUTO_TEST_CASE( ConcordiaSimpleSearch1 )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    concordia.addExample(Example("Ala posiada kota",14));
    concordia.addExample(Example("Ala posiada rysia",51));
    concordia.addExample(Example("Marysia posiada rysia",123));
    concordia.refreshSAfromRAM();
        
    /*The test index contains 3 sentences:    
     14: "Ala posiada kota"
     51: "Ala posiada rysia"
    123: "Marysia posiada rysia"
    
    Test word map:
    Ala -> 0
    posiada -> 1
    kota -> 2
    rysia -> 3
    Marysia -> 4
    
    Test hashed index:
        n: 0  1  2  3  4  5  6  7  8  9 10 11
     T[n]: 0  1  2  |  0  1  3  |  4  1  3  |
    
    Test suffix array:
        n: 0  1  2  3  4  5  6  7  8  9 10 11
    SA[n]: 0  4  1  9  5  2 10  6  8 11  3  7 
    
    */
    
    std::vector<SubstringOccurence> searchResult1 = concordia.simpleSearch("posiada rysia");
    std::vector<SubstringOccurence> searchResult2 = concordia.simpleSearch("posiada kota Ala");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    BOOST_CHECK_EQUAL(searchResult1.size(), 2);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getId(), 123);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getOffset(), 1);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getId(), 51);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getOffset(), 1);
    
    // Checking pattern spanning over 2 segments
    BOOST_CHECK_EQUAL(searchResult2.size(), 0);

}

BOOST_AUTO_TEST_CASE( ConcordiaSimpleSearch2 )
{
    // modified stop words to avoid anonymization 
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    std::vector<Example> testExamples;
    testExamples.push_back(Example("xto xjest okno",312));
    testExamples.push_back(Example("czy xjest okno otwarte",202));
    testExamples.push_back(Example("chyba xto xjest xtutaj",45));
    testExamples.push_back(Example("xto xjest",29));
    concordia.addAllExamples(testExamples);

    /*The test index contains 4 sentences:    
    312: "xto xjest okno"
    202: "czy xjest okno otwarte"
     45: "chyba xto xjest xtutaj"
     29: "xto xjest"
    
    Test word map:
    xto -> 0
    xjest -> 1
    okno -> 2
    czy -> 3
    otwarte -> 4
    chyba -> 5
    xtutaj -> 6
    
    Test hashed index:
        n:  0  1  2  3  4  5  6  7  8  9 10 11 12
     T[n]:  0  1  2  3  1  2  4  5  0  1  6  0  1
    
    Test suffix array:
        n:  0  1  2  3  4  5  6  7  8  9 10 11 12
    SA[n]: 11  0  8 12  1  4  9  2  5  3  6  7 10
    
    */
    
    Concordia concordia2 = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    std::vector<SubstringOccurence> searchResult1 = concordia2.simpleSearch("xto xjest");
    std::vector<SubstringOccurence> searchResult2 = concordia2.simpleSearch("xjest okno");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    BOOST_CHECK_EQUAL(searchResult1.size(), 3);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getId(), 312);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getOffset(), 0);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getId(), 45);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getOffset(), 1);
    BOOST_CHECK_EQUAL(searchResult1.at(2).getId(), 29);
    BOOST_CHECK_EQUAL(searchResult1.at(2).getOffset(), 0);

    BOOST_CHECK_EQUAL(searchResult2.size(), 2);
    BOOST_CHECK_EQUAL(searchResult2.at(0).getId(), 202);
    BOOST_CHECK_EQUAL(searchResult2.at(0).getOffset(), 0);
    BOOST_CHECK_EQUAL(searchResult2.at(1).getId(), 312);
    BOOST_CHECK_EQUAL(searchResult2.at(1).getOffset(), 1);
}

BOOST_AUTO_TEST_CASE( ConcordiaSimpleSearch3 )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    std::vector<Example> testExamples;
    testExamples.push_back(Example("2. Ma on w szczególności prawo do podjęcia zatrudnienia dostępnego na terytorium innego Państwa Członkowskiego z takim samym pierwszeństwem, z jakiego korzystają obywatele tego państwa.",312));
    testExamples.push_back(Example("czy xjest żółte otwarte",202));
    concordia.addAllExamples(testExamples);
    
    Concordia concordia2 = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    std::vector<SubstringOccurence> searchResult1 = concordia2.simpleSearch("on w szczególności prawo do podjęcia");

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    BOOST_CHECK_EQUAL(searchResult1.size(), 1);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getId(), 312);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getOffset(), 1);
}

BOOST_AUTO_TEST_CASE( ConcordiaAnubisSearch1 )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    concordia.addExample(Example("Ala posiada kota",14));
    concordia.addExample(Example("Ala posiada rysia",51));
    concordia.addExample(Example("Marysia posiada rysia",123));
    concordia.refreshSAfromRAM();
        
    /*The test index contains 3 sentences:    
     14: "Ala posiada kota"
     51: "Ala posiada rysia"
    123: "Marysia posiada rysia"
    */

    // the below expectations assume 0.3 anubis threshold
    
    std::vector<AnubisSearchResult> searchResult1 = concordia.anubisSearch("posiada rysia chyba");
    BOOST_CHECK_EQUAL(searchResult1.size(), 2);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getExampleId(), 51);
    BOOST_CHECK_CLOSE(searchResult1.at(0).getScore(), 0.5609, 0.1);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getExampleId(), 123);
    BOOST_CHECK_CLOSE(searchResult1.at(1).getScore(), 0.5609, 0.1);



    std::vector<AnubisSearchResult> searchResult2 = concordia.anubisSearch("Marysia posiada rysia");
    BOOST_CHECK_EQUAL(searchResult2.size(), 2);
    BOOST_CHECK_EQUAL(searchResult2.at(0).getExampleId(), 123);
    BOOST_CHECK_EQUAL(searchResult2.at(0).getScore(), 1);
    BOOST_CHECK_EQUAL(searchResult2.at(1).getExampleId(), 51);
    BOOST_CHECK_CLOSE(searchResult2.at(1).getScore(), 0.5609, 0.1);

    std::vector<AnubisSearchResult> searchResult3 = concordia.anubisSearch("Nowe zdanie");
    BOOST_CHECK_EQUAL(searchResult3.size(), 0);

    std::vector<AnubisSearchResult> searchResult4 = concordia.anubisSearch("Ala posiada kota chyba");
    BOOST_CHECK_EQUAL(searchResult4.size(), 2);
    BOOST_CHECK_EQUAL(searchResult4.at(0).getExampleId(), 14);
    BOOST_CHECK_CLOSE(searchResult4.at(0).getScore(), 0.848, 0.1);
    BOOST_CHECK_EQUAL(searchResult4.at(1).getExampleId(), 51);
    BOOST_CHECK_CLOSE(searchResult4.at(1).getScore(), 0.4707, 0.1);

    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

    /*
    BOOST_CHECK_EQUAL(searchResult1.at(0).getId(), 123);
    BOOST_CHECK_EQUAL(searchResult1.at(0).getOffset(), 1);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getId(), 51);
    BOOST_CHECK_EQUAL(searchResult1.at(1).getOffset(), 1);
    
    // Checking pattern spanning over 2 segments
    BOOST_CHECK_EQUAL(searchResult2.size(), 0);
    */
}

BOOST_AUTO_TEST_SUITE_END()
