/*
 * TimerModel.h
 *
 *  Created on: Jan 19, 2015
 *      Author: xiong.yang
 */

#ifndef TEST_TIMERMODEL_H_
#define TEST_TIMERMODEL_H_

#include <thread>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/QTimer>

class TimerModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	TimerModel();
	virtual ~TimerModel();
	int rowCount(const QModelIndex &parent = QModelIndex()) const
			Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const
			Q_DECL_OVERRIDE;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
			Q_DECL_OVERRIDE;
	void start();
	private slots:
	    void doWork();

private:
	int timer_count;
	std::thread timer_thread;
	QTimer timer;
};

#endif /* TEST_TIMERMODEL_H_ */
