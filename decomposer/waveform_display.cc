#include "waveform_display.hh"

#include <QPainter>
#include <QBrush>
#include <QDebug>

namespace Decomposer {

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
		repaint();
	}
}

void WaveformDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);

	if (buffer_)
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
				y = mid + mid*s*0.9;
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

}
