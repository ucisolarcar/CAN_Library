# Python Integration
### pybind11 library
- https://github.com/pybind/pybind11
- https://pybind11.readthedocs.io/en/stable/basics.html

### Setup
~~~
pip install pybind11
~~~
- clone this repo (if haven't already)
- run the ./build script
- if compiled correctly, a .so file will be outputted into the build/ directory
- two options:
1. move the .so file to the same directory as your python source code
2. add the build directory to Python's path within your program
~~~ python
import sys
sys.path.append('your/path/to/CAN_Library/build')
import PyCANLibrary as canLib
~~~

- Note: let me know if there are any issues with setup

### Usage
- See tests/python_test.py for example usage

### TODO List
- [x] finish MPPT test
- [x] write MCU bindings
- [x] mcu test
- [ ] write LV sensor bindigns
- [ ] LV sensor test
