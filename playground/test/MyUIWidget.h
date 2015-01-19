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


class LevelDBModel;

class MyWindow: public QDialog
{
Q_OBJECT
public:
	explicit MyWindow(QWidget *parent = 0);
	virtual ~MyWindow();

	void setModel(LevelDBModel* model);

public slots:
	void onAddNewPair();

	void onDelete();

signals:
	void DeletelItem(const QString& key);
	void AddNewData(const QString& key, const QString& value);

private:
	Ui::mytest* ui_inst;
	LevelDBModel* model_;
	int timer_count;
};

#endif /* TEST_MYUIWIDGET_H_ */
