#include "main_window.hh"
#include "ui_main_window.h"

#include "audio_source.hh"

#include <QDebug>

namespace Decomposer {

using namespace std::literals;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	source_ = new AudioSource(this);
	source_->setRate(44100);

	ui_->waveform->setDisplayDuration(44100, 10s);

	connect(source_, &AudioSource::newData, ui_->waveform, &WaveformDisplay::addData);
}

MainWindow::~MainWindow()
{
	delete ui_;
}

void MainWindow::on_recordButton_clicked()
{
	qDebug() << "Recording";
	source_->play();
}

}
