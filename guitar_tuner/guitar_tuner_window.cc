#include "guitar_tuner_window.hh"
#include "ui_guitar_tuner_window.h"

namespace Decomposer {

GuitarTunerWindow::GuitarTunerWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GuitarTunerWindow)
{
	ui->setupUi(this);

	connect(ui->inputWidget, &InputWidget::newData, ui->waveformWidget, &WaveformDisplay::addData);
}

GuitarTunerWindow::~GuitarTunerWindow()
{
	delete ui;
}

} // namespace Decomposer
