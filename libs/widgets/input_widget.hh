#pragma once

#include <decomposer/audio_buffer.hh>

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Decomposer {

namespace Ui {
class InputWidget;
}

class AudioSource;

class QDESIGNER_WIDGET_EXPORT InputWidget : public QWidget
{
	Q_OBJECT

public:
	explicit InputWidget(QWidget *parent = 0);
	~InputWidget();

signals:

	void newData(const AudioBuffer& data);

private slots:

	void on_playButton_clicked();
	void on_stopButton_clicked();

private:

	Ui::InputWidget* ui_;
	AudioSource* audioSource_ = nullptr;

};


}
