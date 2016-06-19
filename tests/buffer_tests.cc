#include <decomposer/audio_buffer.hh>

#include <boost/test/unit_test.hpp>

namespace  Decomposer { namespace Tests {

using namespace std::literals;

BOOST_AUTO_TEST_SUITE(AudioBuffer);

BOOST_AUTO_TEST_CASE(CircularBufferSize)
{
	FixedSizeCircularBuffer bufRate10Len1s(10, 1s);
	BOOST_CHECK_EQUAL(bufRate10Len1s.getSampleCapacity(), 10); // expect 10 samples

	FixedSizeCircularBuffer buf8000Len1ms(8000, 1ms);
	BOOST_CHECK_EQUAL(buf8000Len1ms.getSampleCapacity(), 8); // expect 8 samples
}

BOOST_AUTO_TEST_CASE(PushBackWraps)
{
	FixedSizeCircularBuffer buf10(10, 1s);
	BOOST_CHECK_EQUAL(buf10.getSampleCapacity(), 10); // expect 10 samples

	for(int i = 0; i < 12; i++)
	{
		buf10.push_back(double(i));
	}
	// expect the valuies 0 and 1 to be overwritten
	BOOST_CHECK_EQUAL(int(buf10[0]), 2);
	BOOST_CHECK_EQUAL(int(buf10[1]), 3);
	BOOST_CHECK_EQUAL(int(buf10[9]), 11);
}

BOOST_AUTO_TEST_SUITE_END();

}}
