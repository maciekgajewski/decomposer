#include "widgets_plugin.hh"

#include <widgets/waveform_display.hh>
#include <widgets/spectrum_display.hh>
#include <widgets/input_widget.hh>

#include <essentia/algorithmfactory.h>

namespace Decomposer {

WaveformWidgetPlugin::WaveformWidgetPlugin(QObject* p)
	: QObject(p)
{
}

QWidget* WaveformWidgetPlugin::createWidget(QWidget* parent)
{
	return new WaveformDisplay(parent);
}

SpectrumWidgetPlugin::SpectrumWidgetPlugin(QObject* p)
{
}

QWidget* SpectrumWidgetPlugin::createWidget(QWidget* parent)
{
	return new SpectrumDisplay(parent);
}

WidgetsPlugin::WidgetsPlugin(QObject* p)
	: QObject(p)
{
	if (!essentia::isInitialized())
		essentia::init();

	widgets_.push_back(new WaveformWidgetPlugin(this));
	widgets_.push_back(new SpectrumWidgetPlugin(this));
	widgets_.push_back(new InputWidgetPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> WidgetsPlugin::customWidgets() const
{
	return widgets_;
}

InputWidgetPlugin::InputWidgetPlugin(QObject* p)
	: QObject(p)
{
}

QWidget* InputWidgetPlugin::createWidget(QWidget* parent)
{
	return new InputWidget(parent);
}

}


