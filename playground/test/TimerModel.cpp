/*
 * TimerModel.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: xiong.yang
 */


#include <chrono>
#include <iostream>
#include "TimerModel.h"
#include <QApplication>

TimerModel::TimerModel()
: QAbstractTableModel(nullptr)
{
	start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(doWork()));
    timer.start(1000);
}

TimerModel::~TimerModel()
{
	// TODO Auto-generated destructor stub
}

int TimerModel::rowCount(const QModelIndex& parent) const
{
	return 1;
}

int TimerModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

QVariant TimerModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return QString("%1").arg(timer_count);
	}

	return QVariant();
}

void TimerModel::start()
{
	timer_count = 0;
	auto refersh =  [&] ()
		{
			while(true)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				timer_count ++;
				std::cout << "Emit Timer Count " << timer_count <<  std::endl;
			}
		};
	timer_thread = std::thread(refersh);

}
void TimerModel::doWork()
{
	emit dataChanged(index(0,0), index(0,0));
}


#include "TimerModel.moc"
