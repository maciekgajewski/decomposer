#pragma once
#include <QMainWindow>

namespace Decomposer {

namespace Ui {
class MainWindow;
}

class AudioSource;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	void on_recordButton_clicked();

private:
	Ui::MainWindow* ui_ = nullptr;
	AudioSource* source_ = nullptr;
};



}
