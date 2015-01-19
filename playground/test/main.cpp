#include <iostream>
#include <chrono>
#include <thread>
#include "MyUIWidget.h"
#include "LevelDBModel.h"

QApplication* g_app;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	g_app = &app;
	MyWindow inst;
	LevelDBModel dbmodel(argv[1], nullptr);
	inst.setModel(&dbmodel);

//	std::thread flush_thread([&]{while(true){ 	std::this_thread::sleep_for(std::chrono::seconds(1)); ; app.processEvents(); app.flush();}});
	inst.show();
	return app.exec();
}
