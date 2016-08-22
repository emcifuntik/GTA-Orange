#pragma once
class CPyArgBuilder
{
	std::vector<PyObject*> arguments;
	
public:
	CPyArgBuilder& operator<<(long arg)
	{
		arguments.push_back(PyLong_FromLong(arg));
		return *this;
	}
	CPyArgBuilder& operator<<(int arg)
	{
		arguments.push_back(PyInt_FromLong(arg));
		return *this;
	}
	CPyArgBuilder& operator<<(double arg)
	{
		arguments.push_back(PyFloat_FromDouble(arg));
		return *this;
	}
	CPyArgBuilder& operator<<(const char* arg)
	{
		arguments.push_back(PyString_FromString(arg));
		return *this;
	}
	PyObject* Finish()
	{
		PyObject* argList = PyTuple_New(arguments.size());
		int i = 0;
		for each (PyObject* object in arguments)
		{
			PyTuple_SetItem(argList, i, object); //stolen
			i++;
		}
		return argList;
	}

	CPyArgBuilder();
	~CPyArgBuilder();
};

