#include "frequency_meter.hh"

#include <essentia/algorithm.h>
#include <essentia/algorithmfactory.h>

#include <QDebug>

namespace Decomposer {

struct FrequencyMeter::Private
{
	std::vector<essentia::Real> input;
	essentia::Real frequency, confidence;
	std::unique_ptr<essentia::standard::Algorithm> pitchAlgo;
};

FrequencyMeter::FrequencyMeter(QObject *parent) :
	QObject(parent), buffer_(samplingRate_, windowSize_)
{
	p_ = std::make_unique<Private>();
	void setupAlgo();
}

FrequencyMeter::~FrequencyMeter()
{
}

void FrequencyMeter::setWindowSize(int width)
{
	if (width != windowSize_)
	{
		buffer_.setLength(samplingRate_, windowSize_);
		setupAlgo();
	}
}

void FrequencyMeter::setSamplingRate(int rate)
{
	if (rate != samplingRate_)
	{
		buffer_.setLength(samplingRate_, windowSize_);
		setupAlgo();
	}
}

void FrequencyMeter::addData(const AudioBuffer& data)
{
	buffer_.append(data);

	tryMeasureFreqency();
}

void FrequencyMeter::setupAlgo()
{
	p_->input.resize(windowSize_);

	essentia::standard::AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();
	p_->pitchAlgo.reset(factory.create(
		"PitchYin",
		"frameSize", windowSize_,
		"sampleRate", samplingRate_
		));

	p_->pitchAlgo->input("signal").set(p_->input);

	p_->pitchAlgo->output("pitch").set(p_->frequency);
	p_->pitchAlgo->output("pitchConfidence").set(p_->confidence);
}

void FrequencyMeter::tryMeasureFreqency()
{
	 // only measure if buffer is full
	if (buffer_.size() == buffer_.getSampleCapacity())
	{
		p_->input.resize(buffer_.size());
		std::copy(buffer_.begin(), buffer_.end(), p_->input.begin());
		p_->pitchAlgo->compute();

		if (p_->confidence > 0.99)
		{
			emit frequencyDetected(p_->frequency);
			lost_ = false;
		}
		else
		{
			if (!lost_)
			{
				lost_ = true;
				emit frequencyLost();
			}
		}

	}
}

}
