#pragma once

#include <decomposer/audio_buffer.hh>

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Decomposer {

namespace Ui {
class InputWidget;
}

class QDESIGNER_WIDGET_EXPORT InputWidget : public QWidget
{
	Q_OBJECT

public:
	explicit InputWidget(QWidget *parent = 0);
	~InputWidget();

signals:

	void newData(const AudioBuffer& data);

private:
	Ui::InputWidget *ui;
};


}
