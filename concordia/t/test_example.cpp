#include <boost/algorithm/string/predicate.hpp>
#include "tests/unit-tests/unit_tests_globals.hpp"
#include <string>
#include <climits>

#include "concordia/example.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(exampleTest)

BOOST_AUTO_TEST_CASE( ExceedingId )
{
    unsigned long maxId = (ULLONG_MAX >> 8) - 1;
    Example example1("Test", maxId);

    bool exceptionThrown = false;
    string message = "";
    try {
        Example example2("Test", maxId+1);
    } catch (ConcordiaException & e) {
        exceptionThrown = true;
        message = e.what();
    }    
    BOOST_CHECK_EQUAL(exceptionThrown, true);    
    BOOST_CHECK_EQUAL(boost::starts_with(message, "Example id too large"), true);    
}


BOOST_AUTO_TEST_SUITE_END()
