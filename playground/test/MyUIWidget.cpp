/*
 * MyUIWidget.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: xiong.yang
 */

#include "MyUIWidget.h"

MyWindow::MyWindow(QWidget *parent) :
		QDialog(parent), ui_inst(new Ui::mytest())
{
	ui_inst->setupUi(this);
	connect(ui_inst->insert_button_, SIGNAL(released()), this,
			SLOT(onAddNewPair()));
}

MyWindow::~MyWindow()
{
	delete ui_inst;
}

#include "MyUIWidget.moc"
