#include <essentia/algorithmfactory.h>

#include <QApplication>

int main(int argc, char** argv)
{
	essentia::init();

	QApplication app(argc, argv);

	// TODO show window here

	return app.exec();
	essentia::shutdown();
}
