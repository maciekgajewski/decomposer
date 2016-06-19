#include "audio_buffer.hh"

namespace Decomposer {

AudioBuffer::AudioBuffer(unsigned rate)
	: rate_(rate)
{
}

FixedSizeCircularBuffer::FixedSizeCircularBuffer(unsigned rate, Duration length)
{
	setCapacity(rate, length);
}

void FixedSizeCircularBuffer::setLength(unsigned rate, Duration length)
{
	data_.clear();
	setCapacity(rate, length);
}

void FixedSizeCircularBuffer::append(const AudioBuffer& buf)
{
	if (buf.getRate() != rate_)
	{
		throw std::runtime_error("Rate mismatch");
	}
	data_.insert(data_.end(), buf.begin(), buf.end());
}

}
