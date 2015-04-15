#include <iostream>

#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/tm_matches.hpp"
#include "concordia/anubis_searcher.hpp"
#include "concordia/concordia_index.hpp"
#include "concordia/concordia_config.hpp"
#include "concordia/example.hpp"
#include "concordia/hash_generator.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"
#include "concordia/common/logging.hpp"
#include "tests/common/test_resources_manager.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(anubis_searcher)

BOOST_AUTO_TEST_CASE( LcpSearch1 )
{
    AnubisSearcher searcher;
    boost::shared_ptr<std::vector<sauchar_t> > T(new std::vector<sauchar_t>());
    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers(new std::vector<SUFFIX_MARKER_TYPE>());
    boost::shared_ptr<std::vector<saidx_t> > SA(new std::vector<saidx_t>());
    
    /* Search in text: "banana"
       T = 123232 (all one sentence id=34)
       pattern: "anzzz" = 23444
       word map:  b=1,a=2,n=3,z=4
    */

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(1);

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(2);

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(3);

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(2);

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(3);

    T->push_back(0);
    T->push_back(0);
    T->push_back(0);
    T->push_back(2);
    
    for(int i=0;i<6;i++) {
        markers->push_back(Utils::createMarker(34,i,6));
    }
    
    std::vector<sauchar_t> pattern;
    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(2);

    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(3);

    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(4);

    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(0);
    pattern.push_back(4);
    
    /* Suffix array for the hashed index: 0001 0002 0003 0002 0003 0002
         0:000100020003000200030002
        20:0002
        12:000200030002
         4:00020003000200030002
        16:00030002
         8:0003000200030002
         1:00100020003000200030002
        21:002
        13:00200030002
         5:0020003000200030002
        17:0030002
         9:003000200030002
         2:0100020003000200030002
        22:02
        14:0200030002
         6:020003000200030002
        18:030002
        10:03000200030002
         3:100020003000200030002
        23:2
        15:200030002
         7:20003000200030002
        19:30002
        11:3000200030002
    */
    
    SA->push_back(0);
    SA->push_back(20);
    SA->push_back(12);
    SA->push_back(4);
    SA->push_back(16);
    SA->push_back(8);
    SA->push_back(1);
    SA->push_back(21);
    SA->push_back(13);
    SA->push_back(5);
    SA->push_back(17);
    SA->push_back(9);
    SA->push_back(2);
    SA->push_back(22);
    SA->push_back(14);
    SA->push_back(6);
    SA->push_back(18);
    SA->push_back(10);
    SA->push_back(3);
    SA->push_back(23);
    SA->push_back(15);
    SA->push_back(7);
    SA->push_back(19);
    SA->push_back(11);

    SUFFIX_MARKER_TYPE highResLength;
    std::vector<SubstringOccurence> result = searcher.lcpSearch(T, markers, SA, pattern, highResLength);
    SUFFIX_MARKER_TYPE length = highResLength / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get the following results from SA:
        3: ana
        1: anana
       Which are 2 substring occurences (34,3) and (34,1) with the lcp length = 2;  
    */

    BOOST_CHECK_EQUAL(result.size(),2);
    BOOST_CHECK_EQUAL(length,2);
    BOOST_CHECK_EQUAL(result.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result.at(0).getOffset(),3);
    BOOST_CHECK_EQUAL(result.at(1).getId(),34);
    BOOST_CHECK_EQUAL(result.at(1).getOffset(),1);

    //--------pattern banana

    std::vector<sauchar_t> pattern2;
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(1);

    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(2);

    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(3);

    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(2);

    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(3);

    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(0);
    pattern2.push_back(2);

    SUFFIX_MARKER_TYPE highResLength2;
    vector<SubstringOccurence> result2 = searcher.lcpSearch(T, markers, SA, pattern2, highResLength2);
    SUFFIX_MARKER_TYPE length2 = highResLength2 / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get one result from SA:
        0: banana
       Which is one substring occurence (34,0) with the lcp length = 6;
    */


    BOOST_CHECK_EQUAL(result2.size(),1);
    BOOST_CHECK_EQUAL(length2,6);
    BOOST_CHECK_EQUAL(result2.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result2.at(0).getOffset(),0);
    
    //--------pattern banan

    std::vector<sauchar_t> pattern3;
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(1);

    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(2);

    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(3);

    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(2);

    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(0);
    pattern3.push_back(3);

    SUFFIX_MARKER_TYPE highResLength3;
    vector<SubstringOccurence> result3 = searcher.lcpSearch(T, markers, SA, pattern3, highResLength3);
    SUFFIX_MARKER_TYPE length3 = highResLength3 / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get one result from SA:
        0: banana
       Which is one substring occurence (34,0) with the lcp length = 5;
    */

    BOOST_CHECK_EQUAL(result3.size(),1);
    BOOST_CHECK_EQUAL(length3,5);
    BOOST_CHECK_EQUAL(result3.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result3.at(0).getOffset(),0);

    //--------pattern nazz

    std::vector<sauchar_t> pattern4;
    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(3);

    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(2);

    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(4);

    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(0);
    pattern4.push_back(4);

    SUFFIX_MARKER_TYPE highResLength4;
    vector<SubstringOccurence> result4 = searcher.lcpSearch(T, markers, SA, pattern4, highResLength4);
    SUFFIX_MARKER_TYPE length4 = highResLength4 / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get 2 results from SA:
        4: na
        2: nana
       Which are 2 substring occurences (34,4) and (34,2) with the lcp length = 2;
    */

    BOOST_CHECK_EQUAL(result4.size(),2);
    BOOST_CHECK_EQUAL(length4,2);
    BOOST_CHECK_EQUAL(result4.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result4.at(0).getOffset(),4);
    BOOST_CHECK_EQUAL(result4.at(1).getId(),34);
    BOOST_CHECK_EQUAL(result4.at(1).getOffset(),2);
    

    //--------pattern zz

    std::vector<sauchar_t> pattern5;
    pattern5.push_back(0);
    pattern5.push_back(0);
    pattern5.push_back(0);
    pattern5.push_back(4);

    pattern5.push_back(0);
    pattern5.push_back(0);
    pattern5.push_back(0);
    pattern5.push_back(4);

    SUFFIX_MARKER_TYPE highResLength5;
    vector<SubstringOccurence> result5 = searcher.lcpSearch(T, markers, SA, pattern5, highResLength5);
    SUFFIX_MARKER_TYPE length5 = highResLength5 / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get 0 results from SA, lcp length = 0;
    */

    BOOST_CHECK_EQUAL(result5.size(),0);
    BOOST_CHECK_EQUAL(length5,0);

    //--------pattern existing in the text but spanning over parts of characters

    std::vector<sauchar_t> pattern6;
    pattern6.push_back(0);
    pattern6.push_back(0);
    pattern6.push_back(3);

    pattern6.push_back(0);
    pattern6.push_back(0);
    pattern6.push_back(0);
    pattern6.push_back(2);

    pattern6.push_back(0);

    SUFFIX_MARKER_TYPE highResLength6;
    vector<SubstringOccurence> result6 = searcher.lcpSearch(T, markers, SA, pattern5, highResLength6);
    SUFFIX_MARKER_TYPE length6 = highResLength6 / sizeof(INDEX_CHARACTER_TYPE);

    /* Expecting to get 0 results from SA, lcp length = 0;
    */

    BOOST_CHECK_EQUAL(result6.size(),0);
    BOOST_CHECK_EQUAL(length6,0);

}

BOOST_AUTO_TEST_CASE( TmMatchesTest )
{
    AnubisSearcher searcher;

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
    
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX),
                         TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS));
    boost::shared_ptr<ConcordiaConfig> config(
                                new ConcordiaConfig(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg")));
    boost::shared_ptr<HashGenerator> hashGenerator(new HashGenerator(config));

    
    boost::shared_ptr<std::vector<sauchar_t> > T(new std::vector<sauchar_t>());
    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers(new std::vector<SUFFIX_MARKER_TYPE>());

    index.addExample(hashGenerator, T, markers, Example("Ala posiada kota",14));
    index.addExample(hashGenerator, T, markers, Example("Ala posiada rysia",51));
    index.addExample(hashGenerator, T, markers, Example("Marysia posiada rysia",123));

    boost::shared_ptr<std::vector<saidx_t> > SA = index.generateSuffixArray(T);
    
    
    // searching for pattern "Ola posiada rysia Marysia" (5 1 3 4)
    
    std::vector<INDEX_CHARACTER_TYPE> pattern = hashGenerator->generateHash("Ola posiada rysia Marysia");
    
    boost::shared_ptr<TmMatchesMap> tmMatchesMap = searcher.getTmMatches(T, markers, SA, pattern);
    BOOST_CHECK_EQUAL(tmMatchesMap->size(), 3);

    TmMatches * tmMatches14 = tmMatchesMap->find(14)->second;
    TmMatches * tmMatches51 = tmMatchesMap->find(51)->second;
    TmMatches * tmMatches123 = tmMatchesMap->find(123)->second;
    
    BOOST_CHECK_EQUAL(tmMatches14->getExampleId(), 14);
    BOOST_CHECK_EQUAL(tmMatches51->getExampleId(), 51);
    BOOST_CHECK_EQUAL(tmMatches123->getExampleId(), 123);

    // example 14
    // example interval list: [(1,2)] 
    vector<Interval> exampleIntervals14 = tmMatches14->getExampleIntervals();    
    BOOST_CHECK_EQUAL(exampleIntervals14.size(), 1);
    BOOST_CHECK_EQUAL(exampleIntervals14[0].getStart(), 1);
    BOOST_CHECK_EQUAL(exampleIntervals14[0].getEnd(), 2);
    // pattern interval list: [(1,2)] 
    vector<Interval> patternIntervals14 = tmMatches14->getPatternIntervals();    
    BOOST_CHECK_EQUAL(patternIntervals14.size(), 1);
    BOOST_CHECK_EQUAL(patternIntervals14[0].getStart(), 1);
    BOOST_CHECK_EQUAL(patternIntervals14[0].getEnd(), 2);
    
    // example 51
    // example interval list: [(1,3)] 
    vector<Interval> exampleIntervals51 = tmMatches51->getExampleIntervals();    
    BOOST_CHECK_EQUAL(exampleIntervals51.size(), 1);
    BOOST_CHECK_EQUAL(exampleIntervals51[0].getStart(), 1);
    BOOST_CHECK_EQUAL(exampleIntervals51[0].getEnd(), 3);
    // pattern interval list: [(1,3)] 
    vector<Interval> patternIntervals51 = tmMatches51->getPatternIntervals();    
    BOOST_CHECK_EQUAL(patternIntervals51.size(), 1);
    BOOST_CHECK_EQUAL(patternIntervals51[0].getStart(), 1);
    BOOST_CHECK_EQUAL(patternIntervals51[0].getEnd(), 3);
    
    // example 123
    // example interval list: [(1,3), (0,1)] 
    vector<Interval> exampleIntervals123 = tmMatches123->getExampleIntervals();    
    BOOST_CHECK_EQUAL(exampleIntervals123.size(), 2);
    BOOST_CHECK_EQUAL(exampleIntervals123[0].getStart(), 1);
    BOOST_CHECK_EQUAL(exampleIntervals123[0].getEnd(), 3);
    BOOST_CHECK_EQUAL(exampleIntervals123[1].getStart(), 0);
    BOOST_CHECK_EQUAL(exampleIntervals123[1].getEnd(), 1);
    // pattern interval list: [(1,3), (3,4)] 
    vector<Interval> patternIntervals123 = tmMatches123->getPatternIntervals();    
    BOOST_CHECK_EQUAL(patternIntervals123.size(), 2);
    BOOST_CHECK_EQUAL(patternIntervals123[0].getStart(), 1);
    BOOST_CHECK_EQUAL(patternIntervals123[0].getEnd(), 3);
    BOOST_CHECK_EQUAL(patternIntervals123[1].getStart(), 3);
    BOOST_CHECK_EQUAL(patternIntervals123[1].getEnd(), 4);


    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_WORD_MAP)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_MARKERS)); 
    boost::filesystem::remove(TestResourcesManager::getTestFilePath("temp",TEMP_HASHED_INDEX)); 

}


BOOST_AUTO_TEST_SUITE_END()
