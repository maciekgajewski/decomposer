#include "widgets_plugin.hh"

#include <widgets/waveform_display.hh>


namespace Decomposer {

WaveformWidgetPlugin::WaveformWidgetPlugin(QObject* p)
	: QObject(p)
{
}

QWidget* WaveformWidgetPlugin::createWidget(QWidget* parent)
{
	return new WaveformDisplay(parent);
}



}


