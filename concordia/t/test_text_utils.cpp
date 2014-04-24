#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/text_utils.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(text_utils)

BOOST_AUTO_TEST_CASE( ToLower )
{
    string str = "ZAŻÓŁĆ GĘŚLĄ JAŹŃ";
    BOOST_CHECK_EQUAL(TextUtils::toLowerCase(str),"zażółć gęślą jaźń");
}

BOOST_AUTO_TEST_CASE( ToUpper )
{
    string str = "zażółć gęślą jaźń";
    BOOST_CHECK_EQUAL(TextUtils::toUpperCase(str),"ZAŻÓŁĆ GĘŚLĄ JAŹŃ");
}

BOOST_AUTO_TEST_SUITE_END()
