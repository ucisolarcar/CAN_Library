#include <pybind11/pybind11.h>

#include "../src/mppt.h"

namespace py = pybind11;

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
        .def("parsePowerMeasurements", &MPPT::parsePowerMeasurements)
        .def("parseMPPTStatus", &MPPT::parseMPPTStatus)
        .def("getModeName", &MPPT::getModeName)
        .def("getFaultName", &MPPT::getFaultName);
}
