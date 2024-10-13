#include <Python.h>

#include <stdlib.h>


static PyObject* TracerRuntimeError;

static PyObject* spam_system(PyObject* self, PyObject* args) {
    const char* command;
    int status;

    if (!PyArg_ParseTuple(args, "s", &command)) {
        return NULL;
    }
    status = system(command);
    if (!WIFEXITED(status)) {
        return Py_BuildValue("i", -1);
    }
    return Py_BuildValue("i", WEXITSTATUS(status));
}

static PyMethodDef Methods[] = {
    {
        "system",
        spam_system,
        METH_VARARGS,
        "Execute a system command and return its exit status.\n\n"
        "If the command cannot be executed, return -1.",
    },
    {NULL, NULL, 0, NULL},  // sentinel
};

static PyModuleDef tracer_runtime_module = {
    PyModuleDef_HEAD_INIT,
    "tracer_runtime",
    "An example Python C extension module.",
    -1,
    Methods,
};

PyMODINIT_FUNC PyInit_tracer_runtime() {
    PyObject* module;

    module = PyModule_Create(&tracer_runtime_module);
    if (module == NULL) {
        return NULL;
    }
    TracerRuntimeError = PyErr_NewException("tracer_runtime.Error", NULL, NULL);
    Py_INCREF(TracerRuntimeError);
    PyModule_AddObject(module, "Error", TracerRuntimeError);
    return module;
}
