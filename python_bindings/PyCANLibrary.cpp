#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "../src/mppt.h"

namespace py = pybind11;

// Generic wrapper function to convert python byte array to c-style uint8_t array
template <typename ReturnType, typename ClassType>
ReturnType parserWrapper(ClassType& self, py::bytearray data, ReturnType (ClassType::*method)(uint8_t*)) {
    py::buffer_info info = py::buffer(data).request();

    if (info.ndim != 1) {
        throw std::runtime_error("Expected a 1D buffer");
    }

    uint8_t* buf = reinterpret_cast<uint8_t*>(info.ptr);
    size_t length = static_cast<size_t>(info.size);

    return (self.*method)(buf);
}


PYBIND11_MODULE(PyCANLibrary, m) {
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
        .def("parsePowerMeasurements", [](MPPT& self, py::bytearray data) {
            return parserWrapper(self, data, &MPPT::parsePowerMeasurements);
        })
        .def("parseMPPTStatus", [](MPPT& self, py::bytearray data) {
            return parserWrapper(self, data, &MPPT::parseMPPTStatus);
        })
        .def("getModeName", &MPPT::getModeName)
        .def("getFaultName", &MPPT::getFaultName);
}
