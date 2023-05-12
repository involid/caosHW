#include <Python.h>


double Get(PyObject* matrix, size_t i, size_t j) {
    PyObject* item = PyList_GetItem(matrix, i);
    if (item == NULL) {
        return 0.0;
    }
    PyObject* item2 = PyList_GetItem(item, j);
    if (item2 == NULL) {
        return 0.0;
    }
    return PyFloat_AsDouble(item2);
}

PyObject* dot(PyObject* self, PyObject* args_tuple) {
    int matrix_size = 0;
    PyObject* matrix_A = NULL;
    PyObject* matrix_B = NULL;

    if (!PyArg_ParseTuple(args_tuple, "iOO", &matrix_size,
                          &matrix_A,
                          &matrix_B)) {
        return NULL;
    }

    // Result Initialization
    PyObject* result_matrix = PyList_New(matrix_size);
    for (size_t i = 0; i < matrix_size; ++i) {
        PyObject* new_row = PyList_New(matrix_size);
        PyList_SetItem(result_matrix, i, new_row);
    }

    for (size_t i = 0; i < matrix_size; ++i) {
        for (size_t j = 0; j < matrix_size; ++j) {
            double cell_result = 0.0;
            for (size_t k = 0; k < matrix_size; ++k) {
                cell_result += Get(matrix_A, i, k) * Get(matrix_B, k, j);
            }
            PyObject* result_row = PyList_GetItem(result_matrix, i);
            PyList_SetItem(result_row, j, PyFloat_FromDouble(cell_result));
        }
    }

    return result_matrix;
}

static PyMethodDef matrix_methods[] = {
        {
                .ml_name = "dot",
                .ml_meth = dot,
                .ml_flags = METH_VARARGS,
                .ml_doc = "Args: (size, matrix, matrix)"
        },

        // End of list
        { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC PyInit_matrix() {
    static PyModuleDef module_def = {
            .m_base = PyModuleDef_HEAD_INIT,
            .m_name = "matrix",
            .m_size = -1,
            .m_methods = matrix_methods,
    };

    return PyModule_Create(&module_def);
}