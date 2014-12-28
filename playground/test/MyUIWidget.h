/*
 * MyUIWidget.h
 *
 *  Created on: Dec 28, 2014
 *      Author: xiong.yang
 */

#ifndef TEST_MYUIWIDGET_H_
#define TEST_MYUIWIDGET_H_

#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QtWidgets/QDialog>
#include "ui_start.h"

class MyWindow: public QDialog
{
Q_OBJECT
public:
	explicit MyWindow(QWidget *parent = 0);
	virtual ~MyWindow();

	QTableView* GetView()
	{
		return ui_inst->leveldb_view;
	}

public slots:
	void onAddNewPair()
	{
		emit AddNewData(ui_inst->key_edit_->text(),
				ui_inst->value_edit_->text());
		ui_inst->key_edit_->clear();
		ui_inst->value_edit_->clear();
	}
signals:
	void AddNewData(const QString& key, const QString& value);

private:
	Ui::mytest* ui_inst;
};

#endif /* TEST_MYUIWIDGET_H_ */
