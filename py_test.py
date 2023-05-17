# -*- condig: utf-8 -*-
import sys
from test_module import *
from test_module import test_add
import numpy as np


def test_pyc():
    test_add(10, 2)

    test_put_str("test py module")

    out_str =  test_get_str()
    print("get str: ", out_str)

    mul_a = 10.0
    mul_b = 2.0
    mul_c = 5.0
    mul_result = test_multipcation(mul_a, mul_b, mul_c)
    print("multiply: {:f} x {:f} x {:f} = {:f}".format(mul_a, mul_b, mul_c, mul_result))

    mat_a = np.array([1,2,3,4,5,6])
    mat_b = np.array([7,8,9,10,11,12])
    print("mat_a: ", mat_a)
    print("mat_b: ", mat_b)
    mat_c = test_matrix_add(mat_a, mat_b, 2, 3)
    print("mat_c = mat_a + mat_b = ", mat_c)


if __name__ == "__main__":
    print("py test PyObject")
    test_pyc()
    sys.exit()
