# python c api module
## create your c files and write your functions
like, test_pyc.c, test_mutip.c
## write c functions
like, 

```
int test_add(int a, int b)
{
    int c = a + b;
    printf("a = %d\r\n", a);
    printf("b = %d\r\n", b);
    printf("a + b = %d\r\n", c);
    return c;
}
```

---

## create python c wrapper file
like, test_pyc_module.c
---
write wrapper functions, like

```
/**
 * int test_add(int a, int b) wrapper
 */
static PyObject *py_test_add(PyObject *self, PyObject *args)
{
    int a, b;

    // python类型的 args 转换成C类型 a,b
    if(!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    // C类型转换成python类型
    return (PyObject*)Py_BuildValue("i", test_add(a, b));
}
```

## wrap methods
```
static PyMethodDef py_test_methods[] = {
    {"test_add", (PyCFunction)py_test_add, METH_VARARGS, NULL},
    {NULL,NULL}
};
```

## wrap module
```
/**
 * {PyModuleDef_HEAD_INIT, "module_name", "module description", -1, module_methods}
 */
static struct PyModuleDef py_test_methods_module = {
    PyModuleDef_HEAD_INIT,
    "test_module",
    "python c api test methods module",
    -1,
    py_test_methods
};
```

## define init function
```
/**
 * py module init
 * 
 * defined like below:
 * PyMODINIT_FUNC
 * PyInit_xxx(void)
 * {
 * 
 * }
 * 
 * xxx is as same as PyModuleDef module_name
 */
PyMODINIT_FUNC
PyInit_test_module(void)
{
    PyObject *mod;
    mod = PyModule_Create(&py_test_methods_module);
    if(mod == NULL) {
        return NULL;
    }
    return mod;
}
```

# install module
## write setup.py
```
# -*- coding:utf-8 -*-

# terminal run: python setup.py install

from distutils.core import setup, Extension

MOD = "test_module" # defined in test_pyc_module.c
# sources_list = [include called c files, use "," to split]
sources_list = ['test_pyc_module.c','test_pyc.c', 'test_multip.c']

setup(name=MOD,
      version="1.0",
      description="python c api test module", 
      ext_modules=[Extension(MOD, sources=sources_list)]
      )
```
## excute in terminal
$python setup.py install

