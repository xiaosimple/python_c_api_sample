/**
 * python c test wrapper
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "test_pyc.h"
#include <string.h>


/**
 * python C/C++ 接口（API）
 * https://docs.python.org/3/c-api/arg.html
 * 
 * 
 * https://docs.python.org/zh-cn/3/library/array.html?highlight=insert
 * 数值类型
 * 类型码      c类型            python类型      字节尺寸
 * 'b'      signed char         int             1
 * 'B'      usigned char        int             1
 * 'u'      wchar_t             Unicode字符     2
 * 'h'      signed short        int             2
 * 'H'      unsigned short      int             2
 * 'i'      signed int          int             2
 * 'I'      unsigned int        int             2
 * 'l'      signed long         int             4
 * 'L'      unsigned long       int             4
 * 'q'      signed long long    int             8
 * 'Q'      unsigned long long  int             8
 * 'f'      float               float           4
 * 'd'      double              float           8
 * 
 * 
 */

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
    return (PyObject*)Py_BuildValue("ii", test_add(a, b));
}

/**
 * void test_matrix_add(int **a, int **b, uint16_t row, uint16_t col, int **out) wrapper
 */
static PyObject *py_test_matrix_add(PyObject *self, PyObject *args)
{
    PyObject **obj_a;
    PyObject **obj_b;
    uint16_t row;
    uint16_t col;

    // 转换python类型输入参数到C类型
    if(!PyArg_ParseTuple(args, "OOHH", &obj_a, &obj_b, &row, &col)) {
        printf("parse error\r\n");
        Py_DECREF(obj_a);
        Py_DECREF(obj_b);
        return NULL;
    }

    PyObject *seq_a;
    PyObject *seq_b;
    uint16_t seq_a_size = 0;
    uint16_t seq_b_size = 0;
    seq_a = PySequence_Fast(obj_a, "sequence");
    seq_a_size = PySequence_Size(obj_a);
    seq_b = PySequence_Fast(obj_b, "sequence");
    seq_b_size = PySequence_Size(obj_b);

    printf("seq_a_size: %d, seq_b_size: %d, row: %d, col: %d\r\n", seq_a_size, seq_b_size, row, col);

    uint16_t all_size = row * col;
    if(all_size != seq_a_size && all_size != seq_b_size) {
        printf("input row*col is not equal to mat_a size or mat_b size\r\n");
        Py_DECREF(obj_a);
        Py_DECREF(obj_b);
        Py_DECREF(seq_a);
        Py_DECREF(seq_b);
        return NULL;
    }

    int *mat_a;
    int *mat_b;
    int *mat_c;
    mat_a = malloc(all_size*sizeof(int));
    mat_b = malloc(all_size*sizeof(int));
    mat_c = malloc(all_size*sizeof(int));

    if(mat_a == NULL || mat_b == NULL || mat_c == NULL) {
        printf("malloc mat_a or mat_b or mat_c failed\r\n");
        Py_DECREF(obj_a);
        Py_DECREF(obj_b);
        Py_DECREF(seq_a);
        Py_DECREF(seq_b);
        return NULL;
    }

    // PyObject sequence 类型转换成C数组
    PyObject *py_item;
    int item;

    for(uint16_t i = 0; i < all_size; i++) {
        py_item = PySequence_Fast_GET_ITEM(seq_a, i);
        item = PyLong_AS_LONG(py_item);
        *(mat_a+i) = item;
    }
    for(uint16_t i = 0; i <all_size; i++) {
        py_item = PySequence_Fast_GET_ITEM(seq_b, i);
        item = PyLong_AS_LONG(py_item);
        *(mat_b+i) = item;
    }

    test_matrix_add(mat_a, mat_b, row, col, mat_c);

    // mat_c, C类型转换成Python类型
    PyObject *py_out_list = PyList_New(all_size);
    for(uint16_t i = 0; i < all_size; i++) {
        PyList_SetItem(py_out_list, i, Py_BuildValue("H", *(mat_c+i)));
    }
    free(mat_a);
    free(mat_b);
    free(mat_c);

    return py_out_list;
}

/**
 * void test_put_str(char *str) wrapper
 */
static PyObject *py_test_put_str(PyObject *self, PyObject *args)
{
    PyObject *obj;

    if(!PyArg_ParseTuple(args, "s*", &obj)) {
        printf("parse args error\r\n");
        Py_DECREF(obj);
        return NULL;
    }

    // uint16_t str_len = strlen(obj);
    // printf("str len: %d\r\n", str_len);

    test_put_str(obj);

    int ret = 1;
    return (PyObject *)Py_BuildValue("h", ret);
}

/**
 * char *test_get_str(void) wrapper
 */
static PyObject *py_test_get_str(PyObject *self, PyObject *args)
{
    char *str;
    char str_buf[512];
    str = str_buf;

    str = test_get_str();
    uint16_t str_len = 0;
    str_len = strlen(str);

    // printf("get str len: %d\r\n", str_len);
    // printf("get str: %s\r\n", str);

    if(str_len == 0) {
        printf("str len is 0\r\n");
        return NULL;
    }

    PyObject *obj;
    obj = Py_BuildValue("s", str);

    return obj;
}

/**
 * float test_multipcation(float a, float b, float c) wrapper
 */
static PyObject *py_test_multipcation(PyObject *self, PyObject *args)
{
    float a, b, c, d;
    if(!PyArg_ParseTuple(args, "fff", &a, &b, &c)) {
        printf("parse args error\r\n");
        return NULL;
    }

    d = test_multipcation(a, b, c);
    printf("d: %f\r\n", d);
    PyObject *obj;
    obj = Py_BuildValue("f", d);

    return obj;
}


/**
 * static PyObject *py_test_add(PyObject *self, PyObject *args)
 * static PyObject *py_test_matrix_add(PyObject *self, PyObject *args)
 * static PyObject *py_test_put_str(PyObject *self, PyObject *args)
 * static PyObject *py_test_get_str(PyObject *self, PyObject *args)
 * static PyObject *py_test_multipcaton(PyObject *self, PyObject *args)
 * 
 * https://docs.python.org/3/c-api/structures.html
 * {"python called function name, python-c wrapper function name, method, ..."}
 */
static PyMethodDef py_test_methods[] = {
    {"test_add", (PyCFunction)py_test_add, METH_VARARGS, NULL},
    {"test_matrix_add", (PyCFunction)py_test_matrix_add, METH_VARARGS, NULL},
    {"test_put_str", (PyCFunction)py_test_put_str, METH_VARARGS, NULL},
    {"test_get_str", (PyCFunction)py_test_get_str, METH_VARARGS, NULL},
    {"test_multipcation", (PyCFunction)py_test_multipcation, METH_VARARGS, NULL},
    {NULL,NULL}
};

/**
 * {PyModuleDef_HEAD_INIT, "module_name", "module description", -1, module_methods}
 */
static struct PyModuleDef test_methods_module = {
    PyModuleDef_HEAD_INIT,
    "test_module",
    "python c api test methods module",
    -1,
    py_test_methods
};

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
    mod = PyModule_Create(&test_methods_module);
    if(mod == NULL) {
        return NULL;
    }
    return mod;
}
