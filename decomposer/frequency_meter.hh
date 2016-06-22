#pragma once

#include <decomposer/audio_buffer.hh>

#include <QObject>

namespace Decomposer {

class FrequencyMeter : public QObject
{
	Q_OBJECT
public:
	explicit FrequencyMeter(QObject *parent = nullptr);

signals:

	void frequencyDetected(double hz);
	void frequencyLost();

public slots:

	void setWindowWidth(int width);
	void setSamplingRate(int rate);
	void setMinAmplitude(double ma);

public slots:

	void addData(const AudioBuffer& data);

private:

	void tryMeasureFreqency();


	FixedSizeCircularBuffer buffer_;

	// props

	int windowWidth_ = 2048;
	int samplingRate_ = 44100;

	double minAmplitude_ = 0.5;
	bool lost_ = true;
};

}

