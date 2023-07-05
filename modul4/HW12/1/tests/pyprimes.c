#include <Python.h>

int factors_num(int number) {
    if (number < 0) {
        number = -number;
    }
    int num = 0;
    int prime = 2;
    while (number > 1) {
        if (number % prime == 0) {
            number /= prime;
            ++num;
        }
        else {
            ++prime;
        }
    }
    return num;
}

PyObject* factor_out(PyObject* self, PyObject* args_tuple) {
    int number;
    if (!PyArg_ParseTuple(args_tuple, "i", &number)) {
        return NULL;
    }
    int ans_sz = factors_num(number);
    if (ans_sz == 1) {
        return Py_BuildValue("s", "Prime!");
    }
    PyObject* factors = PyList_New(ans_sz + 1);
    PyList_SetItem(factors, 0, PyLong_FromSsize_t(1));
    int prime = 2;
    if (number < 0) {
        number = -number;
    }
    int pos = 1;
    while (number > 1) {
        if (number % prime == 0) {
            PyList_SetItem(factors, pos, PyLong_FromSsize_t(prime));
            ++pos;
            number /= prime;
        }
        else {
            ++prime;
        }
    }
    return factors;
}

static PyMethodDef primes_methods[] = {
        {
                .ml_name = "factor_out",
                .ml_meth = factor_out,
                .ml_flags = METH_VARARGS,
                .ml_doc = "Args: (number)"
        },

        // End of list
        { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC PyInit_primes() {
    static PyModuleDef module_def = {
            .m_base = PyModuleDef_HEAD_INIT,
            .m_name = "primes",
            .m_size = -1,
            .m_methods = primes_methods,
    };

    return PyModule_Create(&module_def);
}