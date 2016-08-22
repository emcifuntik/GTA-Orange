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

	pModule = PyImport_Import(pName);
}
Python::Python()
{
	singleInstance = this;
}
PyObject * Python::pCallFunc(char * fName)
{
	PyObject *pFunc, *pArgs;
	pFunc = PyObject_GetAttrString(Python::Get()->pModule, fName);
	return PyObject_CallObject(pFunc, NULL);

}
