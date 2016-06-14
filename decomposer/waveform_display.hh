#pragma once

#include <QWidget>

namespace Decomposer {

class WaveformDisplay : public QWidget
{
	Q_OBJECT
public:

	explicit WaveformDisplay(QWidget *parent = nullptr);

	void setData(const QByteArray& data);

private:

	void paintEvent(QPaintEvent *event) override;

	QByteArray data_;

};

}
