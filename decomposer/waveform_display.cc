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

		int h = height();
		Sample mid = h*0.5;
		int samples = buffer_->size();

		int toPaint = qMin(samples, width());

		QPointF last(0,0);

		for(int i = 0; i < width(); i++)
		{
			Sample y = mid;
			if (i < samples)
			{
				Sample s = (*buffer_)[i];
				y = mid + mid*s;
			}

			QPointF next(i, y);
			painter.drawLine(last, next);
			last = next;
		}
	}
}

}
