#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/word_map.hpp"

#include <string>
#include <boost/filesystem.hpp>

#define TMP_LOG_FILE "/tmp/concordia.log"

BOOST_AUTO_TEST_SUITE(logging)

BOOST_AUTO_TEST_CASE( LoggingTest )
{
    WordMap wordMap = WordMap();

    SET_LOGGER_FILE(TMP_LOG_FILE);
    SET_LOGGING_LEVEL("ERROR");

    int a = 12414;
    WARN(a);
    
    boost::filesystem::remove(TMP_LOG_FILE);
}

BOOST_AUTO_TEST_SUITE_END()
