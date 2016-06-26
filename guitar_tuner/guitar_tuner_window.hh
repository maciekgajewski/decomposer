#pragma once
#include <QMainWindow>

namespace Decomposer {

namespace Ui {
class GuitarTunerWindow;
}

class GuitarTunerWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GuitarTunerWindow(QWidget *parent = 0);
	~GuitarTunerWindow();

private:
	Ui::GuitarTunerWindow *ui;
};


}
