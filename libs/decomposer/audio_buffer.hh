#pragma once

#include "types.hh"

#include <boost/circular_buffer.hpp>

#include <vector>

namespace Decomposer {

class AudioBuffer
{
public:
	AudioBuffer(unsigned rate);

	std::size_t getSamples() const { return data_.size(); }
	Duration getDuration()
	{
		std::int64_t us = data_.size() * 1000000 / rate_;
		return std::chrono::microseconds(us);
	}

private:

	unsigned rate_; // samples/s
	std::vector<Sample> data_;
};


class FixedSizeCircularBuffer
{
public:

	FixedSizeCircularBuffer(unsigned rate, Duration length);
	void setLength(unsigned rate, Duration length); // erases the current content, changes capacity and ratio
	std::size_t getSampleCapacity() const { return data_.capacity(); }

	std::size_t size() const {return data_.size(); }

	Sample operator[](std::size_t idx) const { return data_[idx]; }

	void push_back(Sample s)
	{
		data_.push_back(s);
	}


private:

	void setCapacity(unsigned rate, Duration length)
	{
		rate_ = rate;
		std::size_t sampleCapacity = length * rate / std::chrono::seconds(1);
		data_.set_capacity(sampleCapacity);
	}

	unsigned rate_; // samples/s
	boost::circular_buffer<Sample> data_;
};


}

