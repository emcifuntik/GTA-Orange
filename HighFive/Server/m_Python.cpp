#include "stdafx.h"

Python* Python::singleInstance = nullptr;

PyMethodDef Python::EmbMethods[] = {
	{ "printMessage", printString, METH_VARARGS, "Return the string recieved from websocket server" },
	{ "playMusic", PlayMusic, METH_VARARGS | METH_KEYWORDS, "Start Listen Music" },
	{ NULL, NULL, 0, NULL }
};

Python* Python::Get()
{
	if (!singleInstance)
		singleInstance = new Python();
	return singleInstance;
}

void Python::Connect(const char * script_name)
{
	pName = PyString_FromString(script_name);
	/* Error checking of pName left out */
	Py_InitModule("HighFive", EmbMethods);
	pModule = PyImport_Import(pName);
}

Python::Python()
{
	Py_Initialize();
	PyObject *sysPath = PySys_GetObject("path");
	PyObject *path = PyString_FromString("scripts");
	int result = PyList_Insert(sysPath, 0, path);
}

PyObject * Python::pCallFunc(char * fName, PyObject* args)
{
	PyObject *pFunc;
	pFunc = PyObject_GetAttrString(Python::Get()->pModule, fName);
	PyObject * value;
	value = PyObject_CallObject(pFunc, args);
	return value;

}
