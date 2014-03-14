#include <boost/algorithm/string/predicate.hpp>
#include "tests/unit-tests/unit_tests_globals.hpp"
#include <string>

#include "concordia/example.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(exampleTest)

BOOST_AUTO_TEST_CASE( ExceedingId )
{
    Example example1("Test", 16777215);

    bool exceptionThrown = false;
    string message = "";
    try {
        Example example2("Test", 16777216);
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Example id too large"), true);    

}


BOOST_AUTO_TEST_SUITE_END()
