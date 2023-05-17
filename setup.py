# -*- coding:utf-8 -*-

# terminal run: python setup.py install

from distutils.core import setup, Extension

MOD = "test_module" # defined in test_pyc_module.c
# sources_list = [include called c files, use "," to split]
sources_list = ['test_pyc_module.c','test_pyc.c', 'test_multip.c']

setup(name=MOD,
      version="0.1",
      description="python c api test module", 
      ext_modules=[Extension(MOD, sources=sources_list)]
      )