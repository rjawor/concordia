#include "tests/unit-tests/unit_tests_globals.hpp"

#include "concordia/concordia_index.hpp"
#include "concordia/concordia_exception.hpp"
#include "tests/common/test_resources_manager.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(concordia_index)


BOOST_AUTO_TEST_CASE( SuffixArrayGenerationTest )
{
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_markers.bin"));
    boost::shared_ptr<vector<sauchar_t> > T = boost::shared_ptr<vector<sauchar_t> >(new vector<sauchar_t>());
    //    Test hashed index:
    //    n: 0 1 2 3 4 5 6 7 8
    // T[n]: 0 1 2 0 1 3 4 1 3 
    T->push_back(0);
    T->push_back(1);
    T->push_back(2);
    T->push_back(0);
    T->push_back(1);
    T->push_back(3);
    T->push_back(4);
    T->push_back(1);
    T->push_back(3);
    
    //    Test suffix array:
    //    n: 0 1 2 3 4 5 6 7 8
    //SA[n]: 0 3 1 7 4 2 8 5 6

    boost::shared_ptr<std::vector<saidx_t> > SA = index.generateSuffixArray(T);

    boost::shared_ptr<vector<saidx_t> > expectedSA = boost::shared_ptr<vector<saidx_t> >(new vector<saidx_t>());
    expectedSA->push_back(0);
    expectedSA->push_back(3);
    expectedSA->push_back(1);
    expectedSA->push_back(7);
    expectedSA->push_back(4);
    expectedSA->push_back(2);
    expectedSA->push_back(8);
    expectedSA->push_back(5);
    expectedSA->push_back(6);
    BOOST_CHECK_EQUAL_COLLECTIONS(SA->begin(), SA->end(), expectedSA->begin(), expectedSA->end());
}

BOOST_AUTO_TEST_CASE( SuffixArrayGenerationTest2 )
{
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_markers.bin"));
    boost::shared_ptr<vector<sauchar_t> > T = boost::shared_ptr<vector<sauchar_t> >(new vector<sauchar_t>());

    //Test hashed index:
    //    n: 0  1  2  3  4  5  6  7  8  9 10 11
    // T[n]: 0  1  2  |  0  1  3  |  4  1  3  |
    T->push_back(0);
    T->push_back(1);
    T->push_back(2);
    T->push_back(255);
    T->push_back(0);
    T->push_back(1);
    T->push_back(3);
    T->push_back(255);
    T->push_back(4);
    T->push_back(1);
    T->push_back(3);
    T->push_back(255);
    
    //Test suffix array:
    //    n: 0  1  2  3  4  5  6  7  8  9 10 11
    //SA[n]: 0  4  1  9  5  2 10  6  8 11  3  7 

    boost::shared_ptr<std::vector<saidx_t> > SA = index.generateSuffixArray(T);

    boost::shared_ptr<vector<saidx_t> > expectedSA = boost::shared_ptr<vector<saidx_t> >(new vector<saidx_t>());
    expectedSA->push_back(0);
    expectedSA->push_back(4);
    expectedSA->push_back(1);
    expectedSA->push_back(9);
    expectedSA->push_back(5);
    expectedSA->push_back(2);
    expectedSA->push_back(10);
    expectedSA->push_back(6);
    expectedSA->push_back(8);
    expectedSA->push_back(11);
    expectedSA->push_back(3);
    expectedSA->push_back(7);
    BOOST_CHECK_EQUAL_COLLECTIONS(SA->begin(), SA->end(), expectedSA->begin(), expectedSA->end());
}

BOOST_AUTO_TEST_CASE( SuffixArrayGenerationTest3 )
{
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"),
                         TestResourcesManager::getTestFilePath("temp","test_markers.bin"));
    boost::shared_ptr<vector<sauchar_t> > T = boost::shared_ptr<vector<sauchar_t> >(new vector<sauchar_t>());

    //Test hashed index:
    //    n: 0  1  2  3  4  5
    // T[n]: 1  2  3  2  3  2
    T->push_back(1);
    T->push_back(2);
    T->push_back(3);
    T->push_back(2);
    T->push_back(3);
    T->push_back(2);
    
    //Test suffix array:
    //    n: 0  1  2  3  4  5
    //SA[n]: 5  3  1  0  4  2

    boost::shared_ptr<std::vector<saidx_t> > SA = index.generateSuffixArray(T);

    boost::shared_ptr<vector<saidx_t> > expectedSA = boost::shared_ptr<vector<saidx_t> >(new vector<saidx_t>());
    expectedSA->push_back(0);
    expectedSA->push_back(5);
    expectedSA->push_back(3);
    expectedSA->push_back(1);
    expectedSA->push_back(4);
    expectedSA->push_back(2);
    BOOST_CHECK_EQUAL_COLLECTIONS(SA->begin(), SA->end(), expectedSA->begin(), expectedSA->end());
}

BOOST_AUTO_TEST_SUITE_END()
