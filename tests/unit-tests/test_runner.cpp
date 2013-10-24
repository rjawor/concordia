#define BOOST_TEST_MODULE Main
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

#include "concordia/common/logging.hpp"

BOOST_AUTO_TEST_CASE(TestRunnerMain) {
    SET_LOGGING_LEVEL("DEBUG");
}
