/*
 * LevelDBModel.cpp
 *
 *  Created on: Dec 26, 2014
 *      Author: xiong.yang
 */

#include "LevelDBModel.h"
#include "LevelDBModel.moc"
#include <QtCore/QTime>
#include <QtCore/QTimer>

#include <cassert>
#include "leveldb/db.h"

LevelDBModel::LevelDBModel(const std::string& dbpath, QObject* parent) :
		QAbstractTableModel(parent)
{
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, dbpath, &db_);
	assert(status.ok());

	//purgeDB();

	for (int i = 0; i < MaxCol; ++i)
	{
		for (int j = 0; j < MaxRow; ++j)
		{
			std::string perfix;
			if (i == 0)
			{
				perfix = "Key ";
			}
			else
			{
				perfix = "Value ";
			}
			std::string index = std::to_string(i) + std::to_string(j);
			m_store_string[i][j] = perfix + index;
		}
	}

}

LevelDBModel::~LevelDBModel()
{
	delete db_;
}

int LevelDBModel::rowCount(const QModelIndex& parent) const
{
	int count = 0;
	auto it = db_->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next())
	{
		count++;
	}
	return count;
}

int LevelDBModel::columnCount(const QModelIndex& parent) const
{
	return MaxCol;
}

QVariant LevelDBModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole /*|| role == Qt::EditRole*/)
	{
		int count = 0;
		auto it = db_->NewIterator(leveldb::ReadOptions());
		for (it->SeekToFirst(); it->Valid(); it->Next(), count++)
		{
			if (index.row() == count)
			{
				if (index.column() == 0)
				{
					return QString(it->key().ToString().c_str());
				}
				else
				{
					return QString(it->value().ToString().c_str());
				}
			}
		}
	}
	else
	{
		return QVariant();
	}
}

QVariant LevelDBModel::headerData(int section, Qt::Orientation orientation,
		int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Key");
			case 1:
				return QString("Value");
			}
		}
	}
	return QVariant();
}

bool LevelDBModel::setData(const QModelIndex & index, const QVariant & value,
		int role)
{
	if (role = Qt::EditRole)
	{
		;
		auto keyindex = QAbstractTableModel::index(index.row(), 0);
		auto key_string = data(keyindex, Qt::DisplayRole).toString();
		db_->Put(leveldb::WriteOptions(), key_string.toStdString(), value.toString().toStdString());
		emit dataChanged(index, index);
	}
	return true;
}

Qt::ItemFlags LevelDBModel::flags(const QModelIndex &index) const
{
	if (index.column() == 0)
	{
		return QAbstractTableModel::flags(index);
	}
	else
	{
		return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
	}
}

void LevelDBModel::InsertNewData(const QString& key, const QString& value)
{
	std::string old_valuexxx;
	auto status = db_->Get(leveldb::ReadOptions(), key.toStdString(),
			&old_valuexxx);

	if (status.IsNotFound())
	{
		status = db_->Put(leveldb::WriteOptions(), key.toStdString(),
				value.toStdString());
		if (status.ok())
		{
			int shouldbe_rowpos = FindKeyIndex(key).first.row();
			insertRows(shouldbe_rowpos, shouldbe_rowpos);
		}
	}
	else if (status.ok()) // the data is already in
	{
	}
	auto indexs = FindKeyIndex(key);
	QModelIndex& keyindex = indexs.first;
	QModelIndex& valueindex = indexs.second;
	emit dataChanged(keyindex, valueindex);
}

std::pair<QModelIndex, QModelIndex> LevelDBModel::FindKeyIndex(
		const QString& keyvalue)
{
	int count = 0;
	auto it = db_->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next())
	{
		if (keyvalue.toStdString() == it->key().ToString())
		{
			return std::make_pair(index(count, 0), index(count, 1));
		}
		count++;
	}

	//the new index should be last one
	return std::make_pair(index(count, 0), index(count, 1));
}

bool LevelDBModel::insertRows(int position, int end_row_number,
		const QModelIndex &)
{
	beginInsertRows(QModelIndex(), position, end_row_number);
	endInsertRows();
	return true;
}
bool LevelDBModel::removeRows(int position, int end_row_number,
		const QModelIndex &index)
{
	beginRemoveRows(QModelIndex(), position, end_row_number);
	endRemoveRows();
	return true;
}

void LevelDBModel::purgeDB()
{
	auto it = db_->NewIterator(leveldb::ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next())
	{
		if (it->key().ToString() == "")
		{
			db_->Delete(leveldb::WriteOptions(), it->key());
		}
	}
}
#include <cassert>
void LevelDBModel::DeleteItem(const QString& key)
{
	auto item_index = FindKeyIndex(key);
	auto status = db_->Delete(leveldb::WriteOptions(), key.toStdString());
	if (status.ok())
	{
		removeRows(item_index.first.row(), item_index.first.row(),
				QModelIndex());
	}
	else
	{
		assert(false);
	}

}
