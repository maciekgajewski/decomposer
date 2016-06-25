#include "spectrum_display.hh"

#include <essentia/algorithmfactory.h>
#include <essentia/algorithm.h>

#include <QPainter>
#include <QDebug>

#include <algorithm>

namespace Decomposer {

static QColor BACKGROUND_COLOR("#33ffd6");

struct SpectrumDisplay::Private
{
	std::vector<essentia::Real> input;
	std::vector<essentia::Real> output;
	std::unique_ptr<essentia::standard::Algorithm> spectrum;
};

SpectrumDisplay::SpectrumDisplay(QWidget* p)
	: QWidget(p)
	, buffer_(sampleRate_, windowSize_)
{
	p_ = std::make_unique<Private>();
	p_->input.resize(windowSize_);

	essentia::standard::AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();
	p_->spectrum.reset(factory.create("Spectrum", "size", 4096));

	p_->spectrum->input("frame").set(p_->input);
	p_->spectrum->output("spectrum").set(p_->output);
}

SpectrumDisplay::~SpectrumDisplay()
{
}

void SpectrumDisplay::addData(const AudioBuffer& data)
{
	buffer_.append(data);
	unpaintedSamples += data.getSamples();
	if (double(unpaintedSamples) / buffer_.getRate() > 0.05 && buffer_.size() == windowSize_)
	{
		calculate();
		repaint();
		unpaintedSamples = 0;
	}

}

void SpectrumDisplay::setWindowSize(int size)
{
	if (size != windowSize_)
	{
		windowSize_ = size;
		buffer_.setLength(sampleRate_, windowSize_);
		unpaintedSamples = 0;
	}
}

void SpectrumDisplay::setSampleRate(int rate)
{
	if (rate != sampleRate_)
	{
		sampleRate_ = rate;
		buffer_.setLength(sampleRate_, windowSize_);
		unpaintedSamples = 0;
	}
}

void SpectrumDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.fillRect(rect(), BACKGROUND_COLOR);
	double h = height();

	int yZoom = 4;
	int xZoom = 16;

	for(size_t i = 0 ; i < p_->output.size()/xZoom; i++)
	{
		float v = p_->output[i];
		double x = double(width()) * i / p_->output.size();
		double y = 2 * h * v / windowSize_;

		// zoom
		y *= yZoom;
		x *= xZoom;

		painter.drawLine(QPointF(x, h), QPointF(x, h-y));
	}
}

void SpectrumDisplay::calculate()
{
	assert(buffer_.size() == windowSize_);

	p_->input.resize(windowSize_);
	std::copy(buffer_.begin(), buffer_.end(), p_->input.begin());

	p_->spectrum->compute();

	qDebug() << "Spectrum size=" << p_->output.size();
	auto max = *std::max_element(p_->output.begin(), p_->output.end());
	auto min = *std::min_element(p_->output.begin(), p_->output.end());
	qDebug() << "range=" << min << ", " << max;
}


}
