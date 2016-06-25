#include "main_window.hh"
#include "ui_main_window.h"

#include "audio_source.hh"
#include "frequency_meter.hh"

#include <essentia/algorithmfactory.h>

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

	ui_->waveform->setSampleRate(44100);
	ui_->waveform->setSamples(4096);

	connect(source_, &AudioSource::newData, ui_->waveform, &WaveformDisplay::addData);
	connect(source_, &AudioSource::newData, ui_->spectrum, &SpectrumDisplay::addData);

	FrequencyMeter* fm = new FrequencyMeter(this);
	fm->setSamplingRate(44100);
	fm->setWindowSize(4096);

	connect(source_, &AudioSource::newData, fm, &FrequencyMeter::addData);
	connect(ui_->minAmplitudeSpin, SIGNAL(valueChanged(double)), fm, SLOT(setMinAmplitude(double)));

	connect(fm, &FrequencyMeter::frequencyDetected, [this](double hz)
		{
			ui_->freqLabel->setText(QString("Freq: %1 Hz").arg(hz));
			ui_->labelFreqLost->clear();
		});
	connect(fm, &FrequencyMeter::frequencyLost, [this]()
		{
			ui_->labelFreqLost->setText("no signal");
		});

	//essentia
	essentia::standard::AlgorithmFactory& factory = essentia::standard::AlgorithmFactory::instance();

	auto algos = factory.keys();
	for(const std::string& algo : algos)
	{
		qDebug() << "* " << QString::fromStdString(algo);
	}

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
