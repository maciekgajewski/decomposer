#include "waveform_display.hh"

#include <QPainter>
#include <QBrush>
#include <QDebug>

namespace Decomposer {

WaveformDisplay::WaveformDisplay(QWidget *parent) :
	QWidget(parent)
{
}

void WaveformDisplay::setData(const QByteArray& data)
{
	data_ = data;
	repaint();
}

void WaveformDisplay::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.fillRect(rect(), Qt::white);
	painter.setPen(Qt::black);

	int h = height();
	int samples = data_.size() / 2; // asuming 16 bit samples

	int toPaint = qMin(samples, width());

	QPoint last(0,0);

	for(int i = 0; i < toPaint; i++)
	{
		qint16 v = *reinterpret_cast<qint16*>(data_.data() + i*2);
		double rescaled = double(v) / 0xffff * h * 0.5;
		QPoint next(i, int(rescaled) + h/2);
		painter.drawLine(last, next);
		last = next;
	}
}

}
