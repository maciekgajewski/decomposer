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

	void paintDense(QPainter& painter);
	void paintSparse(QPainter& painter);

	std::unique_ptr<FixedSizeCircularBuffer> buffer_;
	size_t unpaintedSamples = 0;
};

}
