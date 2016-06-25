#pragma once

#include <decomposer/types.hh>
#include <decomposer/audio_buffer.hh>

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

#include <memory>

namespace Decomposer {

class QDESIGNER_WIDGET_EXPORT SpectrumDisplay : public QWidget
{
	Q_OBJECT
public:

	explicit SpectrumDisplay(QWidget *p = nullptr);
	~SpectrumDisplay();

	int windowSize() const { return windowSize_; }
	int sampleRate() const { return sampleRate_; }

	void addData(const AudioBuffer& data);

	// QWidget

	QSize minimumSizeHint() const override { return QSize(200, 100); }

public slots:

	void setWindowSize(int size);
	void setSampleRate(int rate);

private:

	struct Private;

	void paintEvent(QPaintEvent*) override;
	void calculate();

	int windowSize_ = 4096;
	int sampleRate_ = 44100;


	FixedSizeCircularBuffer buffer_;
	size_t unpaintedSamples = 0;

	std::unique_ptr<Private> p_;
};

}
