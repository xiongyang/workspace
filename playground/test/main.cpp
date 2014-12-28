#include <iostream>

#include "MyUIWidget.h"
#include "LevelDBModel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MyWindow inst;
	LevelDBModel dbmodel(argv[1], nullptr);
	inst.setModel(&dbmodel);

	inst.show();
	return app.exec();
}
