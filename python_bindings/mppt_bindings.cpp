#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "../src/mppt.h"

namespace py = pybind11;


void process_bytes(py::bytearray py_data, uint8_t* &ptr, size_t &length) {
    py::buffer_info info = py::buffer(py_data).request();

    if (info.ndim != 1) {
        throw std::runtime_error("Expected a 1D buffer");
    }

    // The data pointer is a uint8_t* in this case, since Python bytes are byte-oriented.
    ptr = static_cast<uint8_t*>(info.ptr);
    length = static_cast<size_t>(info.size);  // Store the length of the data
}

powerMeasurements parsePowerWrapper(MPPT& self, py::iterable data) {
    uint8_t *ptr;
    size_t length;

    process_bytes(data, ptr, length);

    if (length != 8) {
        std::cout << "ERROR" << std::endl;
    }

    uint8_t buf[length];

    for (int i = 0; i < length; i++) {
        buf[i] = *ptr;  
        ptr++;
    }

    return self.parsePowerMeasurements(buf);
}

PYBIND11_MODULE(mpptpy, m) {
    py::class_<powerMeasurements>(m, "powerMeasurements")
        .def_readwrite("inVoltage", &powerMeasurements::inVoltage)
        .def_readwrite("outVoltage", &powerMeasurements::outVoltage)
        .def_readwrite("inCurrent", &powerMeasurements::inCurrent)
        .def_readwrite("outCurrent", &powerMeasurements::outCurrent);

    py::class_<mpptStatus>(m, "mpptStatus")
        .def_readwrite("mode", &mpptStatus::mode)
        .def_readwrite("fault", &mpptStatus::fault)
        .def_readwrite("enabled", &mpptStatus::enabled)
        .def_readwrite("ambientTemp", &mpptStatus::ambientTemp)
        .def_readwrite("heatsinkTemp", &mpptStatus::heatsinkTemp);

    py::class_<MPPT>(m, "MPPT")
        .def(py::init<>())
        .def("parsePowerMeasurements", &parsePowerWrapper)
        .def("parseMPPTStatus", &MPPT::parseMPPTStatus)
        .def("getModeName", &MPPT::getModeName)
        .def("getFaultName", &MPPT::getFaultName);
}
