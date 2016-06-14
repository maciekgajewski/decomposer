#include "main_window.hh"

#include <QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	Decomposer::MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
