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
    boost::shared_ptr<HashGenerator> hashGenerator (new HashGenerator("nonexistent"));
    
    ConcordiaIndex index(TestResourcesManager::getTestFilePath("temp","test_hash_index.bin"));
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

    boost::shared_ptr<std::vector<saidx_t> > SA = index.generateSuffixArray(hashGenerator, T);

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

BOOST_AUTO_TEST_SUITE_END()
