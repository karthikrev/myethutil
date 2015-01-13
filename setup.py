from distutils.core import setup, Extension

module = Extension("extension", sources = [ 'extension.c' ])

setup(name = 'PackageName', 
        version = '1.0',
        description = 'This is a package for my Module',
        ext_modules = [module])


