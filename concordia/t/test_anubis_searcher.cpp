#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/anubis_searcher.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/utils.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(anubis_searcher)

BOOST_AUTO_TEST_CASE( LcpSearch1 )
{
    AnubisSearcher searcher;
    boost::shared_ptr<std::vector<sauchar_t> > T(new std::vector<sauchar_t>());
    boost::shared_ptr<std::vector<SUFFIX_MARKER_TYPE> > markers(new std::vector<SUFFIX_MARKER_TYPE>());
    boost::shared_ptr<std::vector<saidx_t> > SA(new std::vector<saidx_t>());
    boost::shared_ptr<std::vector<sauchar_t> > pattern(new std::vector<sauchar_t>());
    
    /* Search in text: "banana"
       T = 123232 (all one sentence id=34)
       pattern: "anzzz" = 23444
       word map:  b=1,a=2,n=3,z=4
    */

    T->push_back(1);
    T->push_back(2);
    T->push_back(3);
    T->push_back(2);
    T->push_back(3);
    T->push_back(2);
    
    for(int i=0;i<6;i++) {
        markers->push_back(Utils::createMarker(34,i,6));
    }
    
    pattern->push_back(2);
    pattern->push_back(3);
    pattern->push_back(4);
    pattern->push_back(4);
    
    /* Suffix array for the hashed index: 1 2 3 2 3 2
        0: 1  2  3  2  3  2
        5: 2
        3: 2  3  2
        1: 2  3  2  3  2
        4: 3  2
        2: 3  2  3  2
    */
    
    SA->push_back(0);
    SA->push_back(5);
    SA->push_back(3);
    SA->push_back(1);
    SA->push_back(4);
    SA->push_back(2);

    SUFFIX_MARKER_TYPE length;
    boost::ptr_vector<SubstringOccurence> result = searcher.lcpSearch(T, markers, SA, pattern, length);

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

    boost::shared_ptr<std::vector<sauchar_t> > pattern2(new std::vector<sauchar_t>());
    pattern2->push_back(1);
    pattern2->push_back(2);
    pattern2->push_back(3);
    pattern2->push_back(2);
    pattern2->push_back(3);
    pattern2->push_back(2);

    SUFFIX_MARKER_TYPE length2;
    boost::ptr_vector<SubstringOccurence> result2 = searcher.lcpSearch(T, markers, SA, pattern2, length2);

    /* Expecting to get one result from SA:
        0: banana
       Which is one substring occurence (34,0) with the lcp length = 6;
    */

    BOOST_CHECK_EQUAL(result2.size(),1);
    BOOST_CHECK_EQUAL(length2,6);
    BOOST_CHECK_EQUAL(result2.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result2.at(0).getOffset(),0);
    
    //--------pattern banan

    boost::shared_ptr<std::vector<sauchar_t> > pattern3(new std::vector<sauchar_t>());
    pattern3->push_back(1);
    pattern3->push_back(2);
    pattern3->push_back(3);
    pattern3->push_back(2);
    pattern3->push_back(3);

    SUFFIX_MARKER_TYPE length3;
    boost::ptr_vector<SubstringOccurence> result3 = searcher.lcpSearch(T, markers, SA, pattern3, length3);

    /* Expecting to get one result from SA:
        0: banana
       Which is one substring occurence (34,0) with the lcp length = 5;
    */

    BOOST_CHECK_EQUAL(result3.size(),1);
    BOOST_CHECK_EQUAL(length3,5);
    BOOST_CHECK_EQUAL(result3.at(0).getId(),34);
    BOOST_CHECK_EQUAL(result3.at(0).getOffset(),0);

    //--------pattern nazz

    boost::shared_ptr<std::vector<sauchar_t> > pattern4(new std::vector<sauchar_t>());
    pattern4->push_back(3);
    pattern4->push_back(2);
    pattern4->push_back(4);
    pattern4->push_back(4);

    SUFFIX_MARKER_TYPE length4;
    boost::ptr_vector<SubstringOccurence> result4 = searcher.lcpSearch(T, markers, SA, pattern4, length4);

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
}


BOOST_AUTO_TEST_SUITE_END()
