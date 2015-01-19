/*
 * MyUIWidget.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: xiong.yang
 */

#include "MyUIWidget.h"
#include "LevelDBModel.h"
#include "TimerModel.h"

MyWindow::MyWindow(QWidget *parent) :
		QDialog(parent), ui_inst(new Ui::mytest()), timer_count(0)
{
	ui_inst->setupUi(this);
	connect(ui_inst->insert_button_, SIGNAL(released()), this,
			SLOT(onAddNewPair()));

	connect(ui_inst->del_button_, SIGNAL(released()), this, SLOT(onDelete()));

	ui_inst->timer_view->setModel(new TimerModel());
}

MyWindow::~MyWindow()
{
	delete ui_inst;
}

void MyWindow::setModel(LevelDBModel* model)
{
	model_ = model;
	ui_inst->leveldb_view->setModel(model_);

	connect(this, SIGNAL(AddNewData(const QString& , const QString& )), model_,
			SLOT(InsertNewData(const QString& , const QString& )));

	connect(this, SIGNAL(DeletelItem(const QString& )), model_,
			SLOT(DeleteItem(const QString&)));
}

void MyWindow::onAddNewPair()
{
	emit AddNewData(ui_inst->key_edit_->text(),
			ui_inst->value_edit_->text());
	ui_inst->key_edit_->clear();
	ui_inst->value_edit_->clear();
}

void MyWindow::onDelete()
{
	auto select_mode = ui_inst->leveldb_view->selectionModel();
	if (select_mode->hasSelection())
	{
		auto selection_rows = select_mode->selectedRows(0);
		for (auto each_row_index :  selection_rows)
		{
			auto key = model_->data(each_row_index, Qt::DisplayRole).toString();
			emit DeletelItem(key);
		}
	}
	else
	{
		// No Selection ignore delete command
		return;
	}
	ui_inst->leveldb_view->clearSelection();
}

#include "MyUIWidget.moc"
