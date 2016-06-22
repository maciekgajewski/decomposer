#include "frequency_meter.hh"

#include <QDebug>

namespace Decomposer {

FrequencyMeter::FrequencyMeter(QObject *parent) :
	QObject(parent), buffer_(samplingRate_, windowWidth_)
{
}

void FrequencyMeter::setWindowWidth(int width)
{
	if (width != windowWidth_)
	{
		buffer_.setLength(samplingRate_, windowWidth_);
	}
}

void FrequencyMeter::setSamplingRate(int rate)
{
	if (rate != samplingRate_)
	{
		buffer_.setLength(samplingRate_, windowWidth_);
	}
}

void FrequencyMeter::setMinAmplitude(double ma)
{
	minAmplitude_ = ma;
}


void FrequencyMeter::addData(const AudioBuffer& data)
{
	buffer_.append(data);

	tryMeasureFreqency();
}

void FrequencyMeter::tryMeasureFreqency()
{
	 // only measure if buffer is full
	if (buffer_.size() == buffer_.getSampleCapacity())
	{
		unsigned zeroPasses = 0;
		Sample periodMax = 0.0;
		Sample previousSample = buffer_[0];

		for(unsigned i = 1; i < buffer_.size(); i++)
		{
			Sample s = buffer_[i];

			// detect 0 pass
			if (s > 0)
			{
				if (previousSample <= 0.0)
				{
					if (zeroPasses > 0)
					{
						// verify the max of the previous period
						// if it's too low, reject the value
						if (periodMax < minAmplitude_)
						{
							if (!lost_)
							{
								lost_ = true;
								emit frequencyLost();
							}
							return ;
						}
					}
					periodMax = 0.0;
					zeroPasses ++;
				}
				if (s > periodMax)
					periodMax = s;
			}
			previousSample = s;
		}

		double windowInSeconds = double(windowWidth_) / samplingRate_;
		double hz = double(zeroPasses) / windowInSeconds;

		lost_ = false;
		emit frequencyDetected(hz);
	}
}

}
