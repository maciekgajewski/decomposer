#pragma once

#include <decomposer/types.hh>
#include <decomposer/audio_buffer.hh>

#include <QWidget>

namespace Decomposer {

class WaveformDisplay : public QWidget
{
	Q_OBJECT
public:

	explicit WaveformDisplay(QWidget *parent = nullptr);

	void setDisplayDuration(unsigned rate, Duration d);

public slots:

	void addData(const AudioBuffer& data);

private:

	void paintEvent(QPaintEvent *event) override;

	std::unique_ptr<FixedSizeCircularBuffer> buffer_;
};

}
