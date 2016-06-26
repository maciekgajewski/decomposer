#include "guitar_tuner_window.hh"

#include <essentia/algorithmfactory.h>

#include <QApplication>

int main(int argc, char** argv)
{
	essentia::init();

	QApplication app(argc, argv);

	Decomposer::GuitarTunerWindow window;
	window.show();

	return app.exec();
	essentia::shutdown();
}
