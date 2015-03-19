#include <Python.h>

#include <exception>
#include <stdexcept>
#include <string>
#include <memory>
#include <tuple>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

const char* path = "/home/xiong.yang/workspace/playground/python_embed";
const char* algo = "Algo";

//TODO(xiong) change it return std::shared_ptr<>  so we can set the deleter in it
PyObject* TryLoadFun(PyObject* module, const std::string& fun)
{
	PyObject* py_fun = PyObject_GetAttrString(module, fun.c_str());
	if (py_fun == NULL || !PyCallable_Check(py_fun))
	{
		PyErr_Print();
		std::string error_msg = "Can not load Fun " + fun;
		throw std::invalid_argument(error_msg.c_str());
	}
	return py_fun;
}

typedef std::vector<PyObject*> FunctionsType;
FunctionsType LoadAlogModuel(const char* algo_path, const char* algo_file)
{
	PyObject *python_search_path = PySys_GetObject("path");
	PyObject *algo_path_str = PyString_FromString(algo_path);
	PyList_Insert(python_search_path, 0, algo_path_str);
	auto algo_file_str = PyString_FromString(algo_file);

	auto algo_module = PyImport_Import(algo_file_str);
	Py_DECREF(algo_file_str);

	if (algo_module == NULL)
	{
		PyErr_Print();
		std::string error_msg = std::string("Can not load Module ") + algo_path
				+ "\\" + algo_file;
		throw std::invalid_argument(error_msg.c_str());
	}

	auto algo_on_data = TryLoadFun(algo_module, "OnData");
	auto algo_on_order = TryLoadFun(algo_module, "OnOrder");
	auto algo_on_trade = TryLoadFun(algo_module, "OnTrade");

	return FunctionsType
	{ algo_on_data, algo_on_order, algo_on_trade };
}

void initAlgoAPI(void);
int main(int argc, char *argv[])
{
	Py_Initialize();
	initAlgoAPI();
	auto algo_funs = LoadAlogModuel(path, algo);

	std::thread new_thread([&]()
	{
		for (int i =0; i < 10; ++i)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));

			std::string cpp_market_data
			{	"C++ market data "};
			cpp_market_data += std::to_string(i);
			auto data = PyString_FromString(cpp_market_data.c_str());
			auto pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, data);
			std::cout << "C++ will call PyOnData" << std::endl;
			PyObject_CallObject(algo_funs[0], pArgs);
		}
	});

	new_thread.join();

//	for (int i =0; i < 10; ++i)
//	{
//		std::this_thread::sleep_for(std::chrono::seconds(1));
//
//		std::string cpp_market_data
//		{	"C++ market data "};
//		cpp_market_data += std::to_string(i);
//		auto data = PyString_FromString(cpp_market_data.c_str());
//		auto pArgs = PyTuple_New(1);
//		PyTuple_SetItem(pArgs, 0, data);
//		std::cout << "C++ will call PyOnData" << std::endl;
//		PyObject_CallObject(algo_funs[0], pArgs);
//	}

	Py_Finalize();
	return 0;
}

static PyObject *
AlgoAPI_PlaceOrder(PyObject *self, PyObject* args)
{
	int arg = 0;
	PyArg_ParseTuple(args, "i", &arg);
	std::cout << "C++ code Place Order " << arg << std::endl;
	return nullptr;
}

static PyMethodDef AlgoAPI_methods[] =
{
{ "PlaceOrder", AlgoAPI_PlaceOrder, METH_VARARGS, "AlgoAPI_PlaceOrder" },
{ NULL, NULL } /* sentinel */
};

void initAlgoAPI(void)
{
	PyImport_AddModule("AlgoAPI");
	Py_InitModule("AlgoAPI", AlgoAPI_methods);
}
