#include "frequency_meter.hh"

#include <essentia/algorithm.h>
#include <essentia/algorithmfactory.h>

#include <QDebug>

namespace Decomposer {

struct FrequencyMeter::Private
{
	std::vector<essentia::Real> input;
	std::vector<essentia::Real> filtered;
	essentia::Real frequency, confidence;

	std::unique_ptr<essentia::standard::Algorithm> lowPass;
	std::unique_ptr<essentia::standard::Algorithm> pitchAlgo;
};

FrequencyMeter::FrequencyMeter(QObject *parent) :
	QObject(parent),
	samplingRate_(44100), windowSize_(4096),
	buffer_(samplingRate_, windowSize_)
{
	p_ = std::make_unique<Private>();
	setupAlgo();
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

	p_->lowPass.reset(factory.create(
		"LowPass",
		"cutoffFrequency", 1320, // 4x the highest string freq
		"sampleRate", samplingRate_
		));

	p_->lowPass->input("signal").set(p_->input);
	p_->lowPass->output("signal").set(p_->filtered);

	p_->pitchAlgo->input("signal").set(p_->filtered);

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

		p_->lowPass->compute();
		p_->pitchAlgo->compute();

		AudioBuffer filtered(samplingRate_, p_->filtered.begin(), p_->filtered.end());
		emit onFilteredData(filtered);


		float threshold = 0.99;
		if (p_->frequency > 200)
			threshold = 0.95;
		if (p_->frequency > 300)
			threshold = 0.90;

		if (p_->confidence > threshold)
		{
			emit frequencyDetected(p_->frequency);
			lost_ = false;
			qDebug() << "freq: "<< p_->frequency << " Hz";
		}
		else
		{
			if (!lost_)
			{
				lost_ = true;
				emit frequencyLost();
				qDebug() << "Lost";
			}
		}
	}
}

}
