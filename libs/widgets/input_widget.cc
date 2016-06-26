#include "input_widget.hh"
#include "ui_input_widget.h"

inline void initDecomposerResources() { Q_INIT_RESOURCE(resources); }

namespace Decomposer {

InputWidget::InputWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InputWidget)
{
	::initDecomposerResources();
	ui->setupUi(this);
}

InputWidget::~InputWidget()
{
	delete ui;
}

}
