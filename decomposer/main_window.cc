#include "main_window.hh"
#include "ui_main_window.h"

#include <QAudioInput>
#include <QBuffer>
#include <QDebug>

namespace Decomposer {

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui_(new Ui::MainWindow)
{
	ui_->setupUi(this);

	QAudioFormat format;
	format.setSampleRate(8000);
	format.setChannelCount(1);
	format.setSampleSize(16);
	format.setCodec("audio/pcm");
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setSampleType(QAudioFormat::SignedInt);

	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(format))
	{
		qWarning() << "Default format not supported, trying to use the nearest.";
		format = info.nearestFormat(format);
		qDebug() << format;
	}
	else
	{
		qDebug() << "Format supported";
	}

	input_ = new QAudioInput(format);
	input_->setNotifyInterval(10);
	connect(input_, &QAudioInput::notify, this, &MainWindow::on_audioInputNotify);

	buffer_.reserve(1024*10);
	bufferIo_ = new QBuffer(&buffer_, this);
	bufferIo_->open(QIODevice::WriteOnly);

}

MainWindow::~MainWindow()
{
	delete ui_;
}

void MainWindow::on_recordButton_clicked()
{
	qDebug() << "Recording";
	input_->start(bufferIo_);
}

void MainWindow::on_audioInputNotify()
{
	qDebug() << "Notify, buffer size=" << buffer_.size() << ", io pos=" << bufferIo_->pos();
	//QByteArray copy = buffer_;
	//bufferIo_->seek(0);

	//ui_->waveform->setData(copy);
}

}
