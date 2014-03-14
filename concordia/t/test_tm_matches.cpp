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

BOOST_AUTO_TEST_CASE( TmMatchesLogarithmicScore1 )
{
    TmMatches tmMatches(0,10,10);
    tmMatches.calculateScore();
    
    BOOST_CHECK_EQUAL(tmMatches.getScore(),0.0);
}

BOOST_AUTO_TEST_CASE( TmMatchesLogarithmicScore2 )
{
    TmMatches tmMatches(0,10,10);
    tmMatches.addPatternInterval(0,10);
    tmMatches.addExampleInterval(0,10);
    tmMatches.calculateScore();
    
    BOOST_CHECK_EQUAL(tmMatches.getScore(),1.0);
}

BOOST_AUTO_TEST_CASE( TmMatchesLogarithmicScore3 )
{
    TmMatches tmMatches(0,10,10);
    tmMatches.addPatternInterval(2,5);
    tmMatches.addExampleInterval(1,5);
    tmMatches.calculateScore();
    
    BOOST_CHECK_CLOSE(tmMatches.getScore(),0.2482, 0.1);
}

BOOST_AUTO_TEST_SUITE_END()
