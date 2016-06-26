#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

namespace Decomposer {

//////////////////////////
///// Waveform
class WaveformWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
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

//////////////////////////
///// Spectrum
class SpectrumWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)
public:

	explicit SpectrumWidgetPlugin(QObject* p = nullptr);

	QString name() const override { return "Decomposer::SpectrumDisplay"; }
	QString group() const override { return "Decomposer Widgets"; }
	QString toolTip() const override { return {}; }
	QString whatsThis() const override { return {}; }
	QString includeFile() const override { return "widgets/spectrum_display.hh"; }
	QIcon icon() const override { return {}; }
	bool isContainer() const override { return false; }
	bool isInitialized() const override { return initialized_; }
	void initialize(QDesignerFormEditorInterface *core) { Q_UNUSED(core); initialized_ = true; }
	virtual QString domXml() const
	{
		return QString::fromUtf8("<widget class=\"Decomposer::SpectrumDisplay\" name=\"spectrum_display\"/>");
	}

	QWidget *createWidget(QWidget *parent) override;
private:
	bool initialized_ = false;
};

//////////////////////////
///// Input
class InputWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)
public:

	explicit InputWidgetPlugin(QObject* p = nullptr);

	QString name() const override { return "Decomposer::InputWidget"; }
	QString group() const override { return "Decomposer Widgets"; }
	QString toolTip() const override { return {}; }
	QString whatsThis() const override { return {}; }
	QString includeFile() const override { return "widgets/input_widget.hh"; }
	QIcon icon() const override { return {}; }
	bool isContainer() const override { return false; }
	bool isInitialized() const override { return initialized_; }
	void initialize(QDesignerFormEditorInterface *core) { Q_UNUSED(core); initialized_ = true; }
	virtual QString domXml() const
	{
		return QString::fromUtf8("<widget class=\"Decomposer::InputWidget\" name=\"input_widget\"/>");
	}

	QWidget *createWidget(QWidget *parent) override;
private:
	bool initialized_ = false;
};

////////////
///// Plugin
///
class WidgetsPlugin : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface")
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
public:

	explicit WidgetsPlugin(QObject* p = nullptr);

	QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:

	QList<QDesignerCustomWidgetInterface*> widgets_;
};


}
