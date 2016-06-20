#include "waveform_display.hh"

#include <QPainter>
#include <QBrush>
#include <QDebug>

namespace Decomposer {

static const double HEIGHT_FACTOR = 0.9;

WaveformDisplay::WaveformDisplay(QWidget *parent) :
	QWidget(parent)
{
}

void WaveformDisplay::setDisplayDuration(unsigned rate, Duration d)
{
	buffer_ = std::make_unique<FixedSizeCircularBuffer>(rate, d);
}

void WaveformDisplay::addData(const AudioBuffer& data)
{
	if (buffer_)
	{
		buffer_->append(data);
		unpaintedSamples += data.getSamples();
		if (double(unpaintedSamples) / buffer_->getRate() > 0.05)
		{
			repaint();
			unpaintedSamples = 0;
		}
	}
}

void WaveformDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);

	if (buffer_)
	{
		double samplesPerPixel = double(buffer_->getSampleCapacity()) / width();

		if (samplesPerPixel > 1)
		{
			paintDense(painter);
		}
		else
		{
			paintSparse(painter);
		}
	}
}

void WaveformDisplay::paintDense(QPainter& painter)
{
	painter.setPen(Qt::black);

	int h = height();
	int w = width();
	Sample mid = h*0.5;
	auto samples = buffer_->getSampleCapacity();

	size_t firstSample = 0;
	for(int x = 0; x < w; x++)
	{
		if (firstSample >= buffer_->size())
		{
			// draw straight line till the end
			painter.drawLine(QPoint(x, mid), QPoint(w, mid));
			break;
		}

		size_t lastSample = std::min(
			size_t(std::floor(samples * (x+1)/double(w)))
			, buffer_->size());

		if (lastSample > firstSample)
		{
			int sample = firstSample;
			Sample min = (*buffer_)[sample];
			Sample max = (*buffer_)[sample];
			for(;sample < lastSample; sample++)
			{
				Sample s = (*buffer_)[sample];
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

	auto samples = buffer_->getSampleCapacity();

	for(int i = 0; i < samples; i++)
	{
		double y = mid;
		double x = i * width() / double(samples);
		if (i < buffer_->size())
		{
			Sample s = (*buffer_)[i];
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
