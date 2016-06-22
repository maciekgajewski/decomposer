#include "audio_buffer.hh"

namespace Decomposer {

AudioBuffer::AudioBuffer(unsigned rate)
	: rate_(rate)
{
}

FixedSizeCircularBuffer::FixedSizeCircularBuffer(unsigned rate, Duration length)
{
	std::size_t samples = length * rate / std::chrono::seconds(1);
	setCapacity(rate, samples);
}

FixedSizeCircularBuffer::FixedSizeCircularBuffer(unsigned rate, unsigned samples)
{
	setCapacity(rate, samples);
}


void FixedSizeCircularBuffer::setLength(unsigned rate, unsigned samples)
{
	data_.clear();
	setCapacity(rate, samples);
}

void FixedSizeCircularBuffer::setLength(unsigned rate, Duration length)
{
	data_.clear();
	std::size_t samples = length * rate / std::chrono::seconds(1);
	setCapacity(rate, samples);
}

void FixedSizeCircularBuffer::append(const AudioBuffer& buf)
{
	if (buf.getRate() != rate_)
	{
		throw std::runtime_error("Rate mismatch");
	}
	data_.insert(data_.end(), buf.begin(), buf.end());
}

void FixedSizeCircularBuffer::setCapacity(unsigned rate, unsigned samples)
{
	rate_ = rate;
	data_.set_capacity(samples);
}

}
