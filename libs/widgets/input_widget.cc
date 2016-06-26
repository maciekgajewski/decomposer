#include "input_widget.hh"
#include "ui_input_widget.h"

namespace Decomposer {

InputWidget::InputWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::InputWidget)
{
	ui->setupUi(this);
}

InputWidget::~InputWidget()
{
	delete ui;
}

}
