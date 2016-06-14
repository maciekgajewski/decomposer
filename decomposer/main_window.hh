#pragma once
#include <QMainWindow>

class QAudioInput;
class QBuffer;

namespace Decomposer {

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	void on_recordButton_clicked();
	void on_audioInputNotify();

private:
	Ui::MainWindow* ui_;
	QAudioInput* input_ = nullptr;
	QByteArray buffer_;
	QBuffer* bufferIo_;
};



}
