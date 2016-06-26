#include "input_widget.hh"
#include "ui_input_widget.h"

#include "audio_source.hh"

#include <QAudioDeviceInfo>
#include <QDebug>

inline void initDecomposerResources() { Q_INIT_RESOURCE(resources); }

namespace Decomposer {

InputWidget::InputWidget(QWidget *parent) :
	QWidget(parent),
	ui_(new Ui::InputWidget)
{
	::initDecomposerResources();
	ui_->setupUi(this);

	audioSource_ = new AudioSource(this);

	auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
	foreach(const QAudioDeviceInfo& info, devices)
	{
		ui_->sourceCombo->addItem(info.deviceName(), QVariant::fromValue(info));
	}
	ui_->sourceCombo->setCurrentText(QAudioDeviceInfo::defaultInputDevice().deviceName());

	connect(audioSource_, &AudioSource::newData, this, &InputWidget::newData);
}

InputWidget::~InputWidget()
{
	delete ui_;
}

void InputWidget::on_playButton_clicked()
{
	int idx = ui_->sourceCombo->currentIndex();
	QAudioDeviceInfo deviceInfo = ui_->sourceCombo->itemData(idx).value<QAudioDeviceInfo>();

	audioSource_->setDevice(deviceInfo);
	audioSource_->play();
}

void InputWidget::on_stopButton_clicked()
{
	audioSource_->stop();
}

}
