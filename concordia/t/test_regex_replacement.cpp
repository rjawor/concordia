#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/regex_replacement.hpp"
#include "concordia/common/config.hpp"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/locale.hpp>
#include <boost/algorithm/string/case_conv.hpp>

BOOST_AUTO_TEST_SUITE(regex_replacement)

BOOST_AUTO_TEST_CASE( SimpleReplacement )
{
    RegexReplacement rr("a","b");
    BOOST_CHECK_EQUAL(rr.apply("xxxxxxxaxxxaxxaxaxa"),"xxxxxxxbxxxbxxbxbxb");
}

BOOST_AUTO_TEST_CASE( BadRegex )
{
    bool exceptionThrown = false;
    std::string message = "";
    try {
        RegexReplacement rr("+a","b");
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Bad regex pattern"), true);    
}

BOOST_AUTO_TEST_CASE( WeirdSymbolsReplacement )
{
    RegexReplacement rr("['\"\\\\.]","");
    BOOST_CHECK_EQUAL(rr.apply("Don't stop believin' \\ Hold on to the feelin'."),"Dont stop believin  Hold on to the feelin");
}

BOOST_AUTO_TEST_CASE( BackrefReplacement )
{
    RegexReplacement rr("(\\d+)","the number: \\1");
    BOOST_CHECK_EQUAL(rr.apply("This is 12 and this is 812."),"This is the number: 12 and this is the number: 812.");
}

BOOST_AUTO_TEST_CASE( CaseInsensitiveReplacement )
{
    RegexReplacement rr("abc","xxx", false);
    BOOST_CHECK_EQUAL(rr.apply("This is AbC and ABC and abc and aBC."),"This is xxx and xxx and xxx and xxx.");
}

BOOST_AUTO_TEST_CASE( UnicodeReplacement )
{
    RegexReplacement rr("ą","x");
    BOOST_CHECK_EQUAL(rr.apply("zażółć gęślą jaźń"),"zażółć gęślx jaźń");
}

BOOST_AUTO_TEST_CASE( CaseInsensitiveUnicodeReplacement )
{
    RegexReplacement rr("ą","x", false);
    BOOST_CHECK_EQUAL(rr.apply("zażółć gęślą jaźń ZAŻÓŁĆ GĘŚLĄ JAŹŃ"),"zażółć gęślx jaźń ZAŻÓŁĆ GĘŚLx JAŹŃ");
}

BOOST_AUTO_TEST_CASE( CaseInsensitiveUnicodeClassReplacement )
{
    RegexReplacement rr("[ąćęłńóśżź]","x", false);
    BOOST_CHECK_EQUAL(rr.apply("zażółć gęślą jaźń ZAŻÓŁĆ GĘŚLĄ JAŹŃ"),"zaxxxx gxxlx jaxx ZAxxxx GxxLx JAxx");
}

BOOST_AUTO_TEST_SUITE_END()
