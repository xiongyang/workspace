/*
 * LevelDBModel.h
 *
 *  Created on: Dec 26, 2014
 *      Author: xiong.yang
 */

#ifndef TEST_LEVELDBMODEL_H_
#define TEST_LEVELDBMODEL_H_

#include <string>
#include <QtCore/QAbstractTableModel>

class QTimer;

namespace leveldb
{
class DB;
}

class LevelDBModel: public QAbstractTableModel
{
Q_OBJECT
public:
	LevelDBModel(const std::string& dbpath, QObject *parent);
	virtual ~LevelDBModel();

	int rowCount(const QModelIndex &parent = QModelIndex()) const
			Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const
			Q_DECL_OVERRIDE;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
			Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
			int role) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role =
			Qt::EditRole) Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
public slots:
	void InsertNewData(const QString& key, const QString& value);

private:
	std::pair<QModelIndex, QModelIndex> FindKeyIndex(const QString& keyvalue);
private:
	leveldb::DB* db_;
	QTimer* timer_;
	static const int MaxCol = 2;
	static const int MaxRow = 10;
	std::string m_store_string[MaxCol][MaxRow];
};

#endif /* TEST_LEVELDBMODEL_H_ */
