#include <Python.h>
class Python
{
	Python();
	static Python* singleInstance;
	
	PyObject *pName, *pModule, *pDict;
	static PyObject *printString(PyObject * self, PyObject* args)
	{
		const char * toPrint;
		if (!PyArg_ParseTuple(args, "s", &toPrint))
		{
			return NULL;
		}
		log << toPrint << std::endl;
		Py_RETURN_NONE;
	}
	static PyObject * PlayMusic(PyObject * self, PyObject* args)
	{
		if (!PyArg_ParseTuple(args, ""))
		{
			log << "Not found param list";
			return NULL;
		}
		Py_RETURN_NONE;
	}
	static PyMethodDef EmbMethods[];

public:
	static Python* Get();
	PyObject * pCallFunc(char * fName);
	void Connect(const char * script_name);
	~Python()
	{
		Py_Finalize();
	}
};