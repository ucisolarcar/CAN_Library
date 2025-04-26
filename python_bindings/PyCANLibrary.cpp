#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "../src/mppt.h"
#include "../src/mcu.h"
#include "../src/sensorFunctions.h"

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

    // MPPT ==================================================================
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


    // MCU ===================================================================
        // Bind ControllerStatus struct
    py::class_<ControllerStatus>(m, "ControllerStatus")
        .def(py::init<>())
        .def_readwrite("statusFeedback", &ControllerStatus::statusFeedback)
        .def_readwrite("statusCmd", &ControllerStatus::statusCmd);

    py::class_<MotorData>(m, "MotorData")
    .def(py::init<>())
    .def_readwrite("rpm", &MotorData::rpm)
    .def_readwrite("mcuCurrent", &MotorData::mcuCurrent)
    .def_readwrite("mcuVoltage", &MotorData::mcuVoltage)
    .def_property("mcuFaults",
        [](const MotorData &self) {
            py::list faults;
            for (int i = 0; i < 16; ++i) {
                faults.append(self.mcuFaults[i]);
            }
            return faults;
        },
        [](MotorData &self, py::list faults) {
            if (faults.size() != 16)
                throw std::runtime_error("Expected list of size 16 for mcuFaults");
            for (int i = 0; i < 16; ++i) {
                self.mcuFaults[i] = faults[i].cast<bool>();
            }
        });

    py::class_<ThrottleData>(m, "ThrottleData")
    .def(py::init<>())
    .def_readwrite("mcuThrottle", &ThrottleData::mcuThrottle)
    .def_readwrite("mcuTemp", &ThrottleData::mcuTemp)
    .def_readwrite("motorTemp", &ThrottleData::motorTemp)
    .def_property("swStatus",
        [](const ThrottleData &self) {
            py::list status;
            for (int i = 0; i < 8; ++i) {
                status.append(self.swStatus[i]);
            }
            return status;
        },
        [](ThrottleData &self, py::list status) {
            if (status.size() != 8)
                throw std::runtime_error("Expected list of size 8 for swStatus");
            for (int i = 0; i < 8; ++i) {
                self.swStatus[i] = status[i].cast<bool>();
            }
        }
    )
    .def_readwrite("controllerStatus", &ThrottleData::controllerStatus);

    // Bind MCU class
    py::class_<MCU>(m, "MCU")
        .def(py::init<>())
        .def("parseMotorData", [](MCU& self, py::bytearray data) {
                return parserWrapper(self, data, &MCU::parseMotorData); 
            })
        .def("parseThrottleData", [](MCU& self, py::bytearray data) {
                return parserWrapper(self, data, &MCU::parseThrottleData);
            })

        .def("getFaultStr", &MCU::getFaultStr)
        .def("getSwStatusStr", &MCU::getSwStatusStr)
        .def("getFeedbackStr", &MCU::getFeedbackStr)
        .def("getCommandStr", &MCU::getCommandStr);

        // Bind the floatPair struct
    py::class_<floatPair>(m, "floatPair")
        .def(py::init<>())  // Default constructor
        .def_readwrite("num1", &floatPair::num1)  // Access to num1
        .def_readwrite("num2", &floatPair::num2); // Access to num2

    // Bind the SensorFunctions class
    py::class_<SensorFunctions>(m, "SensorFunctions")
        .def(py::init<>())  // Constructor
        .def("parseCurrent", [](SensorFunctions& self, py::bytearray data) {
                return parserWrapper(self, data, &SensorFunctions::parseCurrent);
            })
        .def("parseVoltage", [](SensorFunctions& self, py::bytearray data) {
                return parserWrapper(self, data, &SensorFunctions::parseVoltage);
            })
        .def("parseTemp", [](SensorFunctions& self, py::bytearray data) {
                return parserWrapper(self, data, &SensorFunctions::parseTemp);
            })
        .def("parseGPS", [](SensorFunctions& self, py::bytearray data) {
                return parserWrapper(self, data, &SensorFunctions::parseGPS);
            });
}
