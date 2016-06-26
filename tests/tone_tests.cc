#include <decomposer/tone.hh>
#include <boost/test/unit_test.hpp>

namespace Decomposer { namespace Tests {

BOOST_AUTO_TEST_SUITE(ToneTests);


BOOST_AUTO_TEST_CASE(ExactA)
{
	Tone t = findClosestTone(440.0);

	BOOST_CHECK_EQUAL(t.name, "A");
	BOOST_CHECK_EQUAL(t.octave, 4);
	BOOST_CHECK_EQUAL(t.index, 0);
	BOOST_CHECK_CLOSE(t.frequency, 440.0, 0.01);
}

BOOST_AUTO_TEST_CASE(AHash4)
{
	Tone t = findClosestTone(466.16);

	BOOST_CHECK_EQUAL(t.name, "A#");
	BOOST_CHECK_EQUAL(t.octave, 4);
	BOOST_CHECK_EQUAL(t.index, 1);
	BOOST_CHECK_CLOSE(t.frequency, 466.16, 0.01);
}

BOOST_AUTO_TEST_CASE(GHash4)
{
	Tone t = findClosestTone(415.30);

	BOOST_CHECK_EQUAL(t.name, "G#");
	BOOST_CHECK_EQUAL(t.octave, 4);
	BOOST_CHECK_EQUAL(t.index, -1);
	BOOST_CHECK_CLOSE(t.frequency, 415.30, 0.01);
}

BOOST_AUTO_TEST_CASE(A1)
{
	Tone t = findClosestTone(55.0);

	BOOST_CHECK_EQUAL(t.name, "A");
	BOOST_CHECK_EQUAL(t.octave, 1);
	BOOST_CHECK_EQUAL(t.index, -36);
	BOOST_CHECK_CLOSE(t.frequency, 55.0, 0.01);
}

BOOST_AUTO_TEST_CASE(C0)
{
	Tone t = findClosestTone(16.35);

	BOOST_CHECK_EQUAL(t.name, "C");
	BOOST_CHECK_EQUAL(t.octave, 0);
	BOOST_CHECK_CLOSE(t.frequency, 16.35, 0.01);
}

BOOST_AUTO_TEST_CASE(G8)
{
	Tone t = findClosestTone(6271.93);

	BOOST_CHECK_EQUAL(t.name, "G");
	BOOST_CHECK_EQUAL(t.octave, 8);
	BOOST_CHECK_CLOSE(t.frequency, 6271.93, 0.01);
}

BOOST_AUTO_TEST_CASE(B8)
{
	Tone t = findClosestTone(7902.13);

	BOOST_CHECK_EQUAL(t.name, "B");
	BOOST_CHECK_EQUAL(t.octave, 8);
	BOOST_CHECK_CLOSE(t.frequency, 7902.13, 0.01);
}

BOOST_AUTO_TEST_SUITE_END();

}}

