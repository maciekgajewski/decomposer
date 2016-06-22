#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

namespace Decomposer {

class WaveformWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
	Q_INTERFACES(QDesignerCustomWidgetInterface)
public:

	explicit WaveformWidgetPlugin(QObject* p = nullptr);

	QString name() const override { return "Decomposer::WaveformDisplay"; }
	QString group() const override { return "Decomposer Widgets"; }
	QString toolTip() const override { return {}; }
	QString whatsThis() const override { return {}; }
	QString includeFile() const override { return "widgets/waveform_display.hh"; }
	QIcon icon() const override { return {}; }
	bool isContainer() const override { return false; }
	bool isInitialized() const override { return initialized_; }
	void initialize(QDesignerFormEditorInterface *core) { Q_UNUSED(core); initialized_ = true; }
	virtual QString domXml() const
	{
		return QString::fromUtf8("<widget class=\"Decomposer::WaveformDisplay\" name=\"waveform_display\"/>");
	}

	QWidget *createWidget(QWidget *parent) override;
private:
	bool initialized_ = false;
};

}
