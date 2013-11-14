#include "tests/unit-tests/unit_tests_globals.hpp"

#include "concordia/concordia_index.hpp"
#include "tests/common/test_resources_manager.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(concordia_index)

BOOST_AUTO_TEST_CASE( ResourcesExistenceTest1 )
{
    ConcordiaIndex index(TestResourcesManager::getTestWordMapFilePath("mock_word_map.bin"),
                         TestResourcesManager::getTestHashIndexFilePath("mock_hash_index.bin"),
                         TestResourcesManager::getTestSuffixArrayFilePath());
                         
}

BOOST_AUTO_TEST_SUITE_END()
