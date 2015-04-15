#include "tests/unit-tests/unit_tests_globals.hpp"
#include "concordia/interval.hpp"
#include "concordia/common/config.hpp"

BOOST_AUTO_TEST_SUITE(interval)

BOOST_AUTO_TEST_CASE( IntervalIntersects1 )
{
	Interval interval1(2,5);
	Interval interval2(6,7);
    BOOST_CHECK(!interval1.intersects(interval2));
    BOOST_CHECK(!interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects2 )
{
	Interval interval1(2,5);
	Interval interval2(5,7);
    BOOST_CHECK(!interval1.intersects(interval2));
    BOOST_CHECK(!interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects3 )
{
	Interval interval1(2,5);
	Interval interval2(4,7);
    BOOST_CHECK(interval1.intersects(interval2));
    BOOST_CHECK(interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects4 )
{
	Interval interval1(3,5);
	Interval interval2(3,7);
    BOOST_CHECK(interval1.intersects(interval2));
    BOOST_CHECK(interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects5 )
{
	Interval interval1(4,5);
	Interval interval2(3,7);
    BOOST_CHECK(interval1.intersects(interval2));
    BOOST_CHECK(interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects6 )
{
	Interval interval1(4,9);
	Interval interval2(3,7);
    BOOST_CHECK(interval1.intersects(interval2));
    BOOST_CHECK(interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects7 )
{
	Interval interval1(7,9);
	Interval interval2(3,7);
    BOOST_CHECK(!interval1.intersects(interval2));
    BOOST_CHECK(!interval2.intersects(interval1));
}

BOOST_AUTO_TEST_CASE( IntervalIntersects8 )
{
	Interval interval1(8,9);
	Interval interval2(3,7);
    BOOST_CHECK(!interval1.intersects(interval2));
    BOOST_CHECK(!interval2.intersects(interval1));
}

BOOST_AUTO_TEST_SUITE_END()
