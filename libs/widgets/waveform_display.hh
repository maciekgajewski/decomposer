#pragma once

#include <decomposer/types.hh>
#include <decomposer/audio_buffer.hh>

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Decomposer {

class QDESIGNER_WIDGET_EXPORT WaveformDisplay : public QWidget
{
	Q_OBJECT
public:

	explicit WaveformDisplay(QWidget *parent = nullptr);

public slots:

	void addData(const AudioBuffer& data);

	// props

	void setSampleRate(int rate);
	void setSamples(int samples);

public:

	// props

	int sampleRate() const { return sampleRate_; }
	int samples() const { return samples_; }

	// QWidget

	QSize minimumSizeHint() const override { return QSize(200, 100); }

private:

	void paintEvent(QPaintEvent*) override;
	void resizeEvent(QResizeEvent*) override;

	void paintDense(QPainter& painter);
	void paintSparse(QPainter& painter);
	void prepareBackground();

	FixedSizeCircularBuffer buffer_;
	size_t unpaintedSamples = 0;
	QPixmap background_;

	// config
	int samples_ = 2048;
	int sampleRate_ = 44100;
};

}
