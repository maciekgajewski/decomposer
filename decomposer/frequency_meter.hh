#pragma once

#include <decomposer/audio_buffer.hh>

#include <QObject>

#include <memory>

namespace Decomposer {

class FrequencyMeter : public QObject
{
	Q_OBJECT
public:
	explicit FrequencyMeter(QObject *parent = nullptr);
	~FrequencyMeter();

signals:

	void frequencyDetected(double hz);
	void frequencyLost();

public slots:

	void setWindowSize(int width);
	void setSamplingRate(int rate);

public slots:

	void addData(const AudioBuffer& data);

private:

	struct Private;

	void setupAlgo();
	void tryMeasureFreqency();

	FixedSizeCircularBuffer buffer_;

	// props

	int windowSize_ = 2048;
	int samplingRate_ = 44100;

	bool lost_ = true;

	std::unique_ptr<Private> p_;
};

}

