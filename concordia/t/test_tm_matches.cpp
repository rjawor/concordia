#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/interval.hpp"
#include "concordia/tm_matches.hpp"
#include "concordia/common/config.hpp"

using namespace std;

BOOST_AUTO_TEST_SUITE(tm_matches)

BOOST_AUTO_TEST_CASE( TmMatchesSimpleScore1 )
{
    TmMatches tmMatches(0,10,10);
    tmMatches.addPatternInterval(2,5);
    tmMatches.addExampleInterval(1,5);
    tmMatches.calculateSimpleScore();
    
    BOOST_CHECK_EQUAL(tmMatches.getScore(),0.35);
}

BOOST_AUTO_TEST_SUITE_END()
