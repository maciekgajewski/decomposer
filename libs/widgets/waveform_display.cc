#include "waveform_display.hh"

#include <QPainter>
#include <QBrush>
#include <QDebug>

namespace Decomposer {

static const double HEIGHT_FACTOR = 0.9;
static const QColor BACKGROUND_COLOR = QColor("#ffe6cc");

WaveformDisplay::WaveformDisplay(QWidget *parent)
	:	QWidget(parent)
	,	buffer_(sampleRate_, bufferSamples())
{
}

void WaveformDisplay::addData(const AudioBuffer& data)
{
	buffer_.append(data);
	unpaintedSamples += data.getSamples();
	if (double(unpaintedSamples) / buffer_.getRate() > 0.05)
	{
		repaint();
		unpaintedSamples = 0;
	}
}

void WaveformDisplay::setSampleRate(int rate)
{
	if (rate != sampleRate_)
	{
		sampleRate_ = rate;
		buffer_.setLength(sampleRate_, bufferSamples());

		prepareBackground();
		repaint();
	}
}

void WaveformDisplay::setSamples(int samples)
{
	if (samples != samples_)
	{
		if (samples > 4096)
		{
			qWarning() << "Waveform limited to dsiplay 4096 samples";
			return;
		}

		samples_ = samples;
		buffer_.setLength(sampleRate_, bufferSamples());

		prepareBackground();
		repaint();
	}
}

void WaveformDisplay::prepareBackground()
{
	QSize sz = size();
	background_ = QPixmap(sz);
	background_.fill(BACKGROUND_COLOR );

	QColor lineColor("#e64d00");
	QPainter painter(&background_);

	painter.setPen(lineColor);
	int mid = sz.height() / 2;
	painter.drawLine(0, mid, sz.width(), mid);

	QFont font("Monospace", 8);
	font.setStyleHint(QFont::TypeWriter);
	font.setPointSize(8);

	painter.setFont(font);

	QFontMetrics metrics(font, this);
	QString text = QString("%1 samples, %2 per second").arg(samples_).arg(sampleRate_);

	painter.drawText(10, 10 + metrics.height(), text);
}

size_t WaveformDisplay::bufferSamples() const
{
	// Calculates the number of samples we want to store in a buffer
	size_t margin = sampleRate_ / 50; // store enough to have 1 extra 50Hz cycle
	return sampleRate_ + margin;
}

size_t WaveformDisplay::findStartSample() const
{
	// return the index a a fist sample to display
	size_t idx = 0;
	Sample s = buffer_[0];
	for(;idx < buffer_.size(); idx++)
	{
		if (s <= 0.0 && buffer_[idx] > 0.0)
		{
			return idx;
		}
		s = buffer_[idx];
	}
	return idx;
}


void WaveformDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, background_);

	if (!buffer_.empty())
	{
		double samplesPerPixel = double(buffer_.getSampleCapacity()) / width();

		size_t firstSample = findStartSample();
		size_t lastSample = std::min(samples_ + firstSample, buffer_.size());

		if (samplesPerPixel > 1)
		{
			paintDense(painter,	firstSample, lastSample);
		}
		else
		{
			paintSparse(painter, firstSample, lastSample);
		}
	}
}

void WaveformDisplay::resizeEvent(QResizeEvent*)
{
	prepareBackground();
}

void WaveformDisplay::paintDense(QPainter& painter, size_t firstSample, size_t lastSample)
{
	painter.setPen(Qt::black);

	int h = height();
	int w = width();
	Sample mid = h*0.5;

	for(int x = 0; x < w; x++)
	{
		if (firstSample >= lastSample)
		{
			break;
		}

		size_t lastInSection = std::min(
			size_t(std::floor(samples_ * (x+1)/double(w)))
			, lastSample);

		if (lastInSection > firstSample)
		{
			int sample = firstSample;
			Sample min = buffer_[sample];
			Sample max = buffer_[sample];
			for(;sample < lastInSection; sample++)
			{
				Sample s = buffer_[sample];
				if (s > max) max = s;
				if (s < min) min = s;
			}
			firstSample = lastInSection;

			int ymin = mid + mid*min*HEIGHT_FACTOR;
			int ymax = mid + mid*max*HEIGHT_FACTOR;

			painter.drawLine(QPoint(x, ymin), QPoint(x, ymax));
		}
	}
}

void WaveformDisplay::paintSparse(QPainter& painter, size_t firstSample, size_t lastSample)
{
	painter.setPen(Qt::black);
	painter.setRenderHint(QPainter::Antialiasing);

	int h = height();
	Sample mid = h*0.5;

	QPointF last(0,0);

	for(int i = firstSample; i < lastSample; i++)
	{
		double y = mid;
		double x = i * width() / double(samples_);
		Sample s = buffer_[i];
		y = mid + mid*s*HEIGHT_FACTOR;

		QPointF next(x, y);
		if (i > 0 )
		{
			painter.drawLine(last, next);
		}
		last = next;
	}
}

}
