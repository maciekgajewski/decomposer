#include "main_window.hh"

#include <essentia/algorithmfactory.h>

#include <QApplication>

int main(int argc, char** argv)
{
	essentia::init();

	QApplication app(argc, argv);

	Decomposer::MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
