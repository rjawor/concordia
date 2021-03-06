#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/common/config.hpp"
#include "concordia/common/text_utils.hpp"

BOOST_AUTO_TEST_SUITE(text_utils)

BOOST_AUTO_TEST_CASE( ToLower )
{
    std::string str = "ZAŻÓŁĆ GĘŚLĄ JAŹŃ";
    BOOST_CHECK_EQUAL(TextUtils::getInstance().toLowerCase(str),"zażółć gęślą jaźń");
}

BOOST_AUTO_TEST_CASE( ToUpper )
{
    std::string str = "zażółć gęślą jaźń";
    BOOST_CHECK_EQUAL(TextUtils::getInstance().toUpperCase(str),"ZAŻÓŁĆ GĘŚLĄ JAŹŃ");
}

BOOST_AUTO_TEST_SUITE_END()
