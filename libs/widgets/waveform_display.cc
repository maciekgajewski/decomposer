#include "waveform_display.hh"

#include <QPainter>
#include <QBrush>
#include <QDebug>

namespace Decomposer {

static const double HEIGHT_FACTOR = 0.9;
static const QColor BACKGROUND_COLOR = QColor("#ffe6cc");

WaveformDisplay::WaveformDisplay(QWidget *parent)
	:	QWidget(parent)
	,	buffer_(sampleRate_, samples_)
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
		buffer_.setLength(sampleRate_, samples_);

		prepareBackground();
		repaint();
	}
}

void WaveformDisplay::setSamples(int samples)
{
	if (samples != samples_)
	{
		samples_ = samples;
		buffer_.setLength(sampleRate_, samples_);

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


void WaveformDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, background_);

	double samplesPerPixel = double(buffer_.getSampleCapacity()) / width();

	if (samplesPerPixel > 1)
	{
		paintDense(painter);
	}
	else
	{
		paintSparse(painter);
	}
}

void WaveformDisplay::resizeEvent(QResizeEvent*)
{
	prepareBackground();
}

void WaveformDisplay::paintDense(QPainter& painter)
{
	painter.setPen(Qt::black);

	int h = height();
	int w = width();
	Sample mid = h*0.5;
	auto samples = buffer_.getSampleCapacity();

	size_t firstSample = 0;
	for(int x = 0; x < w; x++)
	{
		if (firstSample >= buffer_.size())
		{
			break;
		}

		size_t lastSample = std::min(
			size_t(std::floor(samples * (x+1)/double(w)))
			, buffer_.size());

		if (lastSample > firstSample)
		{
			int sample = firstSample;
			Sample min = buffer_[sample];
			Sample max = buffer_[sample];
			for(;sample < lastSample; sample++)
			{
				Sample s = buffer_[sample];
				if (s > max) max = s;
				if (s < min) min = s;
			}
			firstSample = lastSample;

			int ymin = mid + mid*min*HEIGHT_FACTOR;
			int ymax = mid + mid*max*HEIGHT_FACTOR;

			painter.drawLine(QPoint(x, ymin), QPoint(x, ymax));
		}
	}
}

void WaveformDisplay::paintSparse(QPainter& painter)
{
	painter.setPen(Qt::black);
	painter.setRenderHint(QPainter::Antialiasing);

	int h = height();
	Sample mid = h*0.5;

	QPointF last(0,0);

	auto samples = buffer_.getSampleCapacity();

	for(int i = 0; i < samples; i++)
	{
		double y = mid;
		double x = i * width() / double(samples);
		if (i < buffer_.size())
		{
			Sample s = buffer_[i];
			y = mid + mid*s*HEIGHT_FACTOR;
		}

		QPointF next(x, y);
		if (i > 0 )
		{
			painter.drawLine(last, next);
		}
		last = next;
	}
}

}
