#pragma once

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

private:
	Ui::InputWidget *ui;
};


}
