#include <iostream>

#include "MyUIWidget.h"
#include "LevelDBModel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyWindow inst;
	LevelDBModel dbmodel(argv[1], nullptr);
	inst.GetView()->setModel(&dbmodel);

	QObject::connect(&inst,
			SIGNAL(AddNewData(const QString& , const QString& )), &dbmodel,
			SLOT(InsertNewData(const QString& , const QString& )));

	inst.show();
	return app.exec();
}
