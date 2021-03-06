#pragma once

#include <decomposer/types.hh>
#include <decomposer/audio_buffer.hh>

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Decomposer {

class QDESIGNER_WIDGET_EXPORT WaveformDisplay : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate)
	Q_PROPERTY(int samplese READ samples WRITE setSamples)
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

	void paintSparse(QPainter& painter, size_t firstSample, size_t lastSample);
	void prepareBackground();

	size_t bufferSamples() const;
	size_t findStartSample() const;

	int samples_;
	int sampleRate_;

	FixedSizeCircularBuffer buffer_;
	size_t unpaintedSamples = 0;
	QPixmap background_;

};

}
