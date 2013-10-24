#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/concordia.hpp"
#include "tests/common/test_resources_manager.hpp"


#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(concordia_main)

BOOST_AUTO_TEST_CASE( ConcordiaVersion )
{
    Concordia concordia = Concordia(TestResourcesManager::getTestConcordiaConfigFilePath("concordia.cfg"));
    string version = concordia.getVersion();
    BOOST_CHECK_EQUAL( version , "0.1");
}

BOOST_AUTO_TEST_SUITE_END()
