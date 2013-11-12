#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/word_map.hpp"

#include <string>

using namespace std;

BOOST_AUTO_TEST_SUITE(word_map)

BOOST_AUTO_TEST_CASE( WordCodeTest )
{
    WordMap wordMap = WordMap();

    BOOST_CHECK_EQUAL(wordMap.getWordCode("abc") , 0);
    BOOST_CHECK_EQUAL(wordMap.getWordCode("def") , 1);
    BOOST_CHECK_EQUAL(wordMap.getWordCode("abc") , 0);
    BOOST_CHECK_EQUAL(wordMap.getWordCode("ghi") , 2);
    BOOST_CHECK_EQUAL(wordMap.getWordCode("g") , 3);
    BOOST_CHECK_EQUAL(wordMap.getWordCode(".;?") , 4);
    BOOST_CHECK_EQUAL(wordMap.getWordCode("g") , 3);
}

BOOST_AUTO_TEST_SUITE_END()
