#include "guitar_tuner_window.hh"
#include "ui_guitar_tuner_window.h"

#include "frequency_meter.hh"

namespace Decomposer {

GuitarTunerWindow::GuitarTunerWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GuitarTunerWindow)
{
	ui->setupUi(this);

	//connect(ui->inputWidget, &InputWidget::newData, ui->waveformWidget, &WaveformDisplay::addData);

	FrequencyMeter* fm = new FrequencyMeter(this);

	connect(ui->inputWidget, &InputWidget::newData, fm, &FrequencyMeter::addData);
	connect(fm, &FrequencyMeter::onFilteredData, ui->waveformWidget, &WaveformDisplay::addData);
}

GuitarTunerWindow::~GuitarTunerWindow()
{
	delete ui;
}

} // namespace Decomposer
