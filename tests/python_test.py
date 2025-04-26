import sys
sys.path.append('./build')
import PyCANLibrary as canLib # my mppt parsing library

# ============================== MPPT PARSING =================================
mppt = canLib.MPPT()

print("\nTesting MPPT Power Measurement Parsing")
print("---------------------------------------")
# these are the hex values of the expected values shown below
frame = bytearray([0xf7, 0x68, 0xc1, 0x81, 0xf6, 0xa0, 0xb1, 0xe0])
print("The expected values are as follows:")
print("Input voltage: ", -22)
print("Input current: ", -7.9995)
print("Output voltage: ", -24)
print("Output current: ", -10)

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

# Returns a powerMeasurements object
power = mppt.parsePowerMeasurements(frame)

# display results
print("Here are the results:")
print("Input voltage: ", power.inVoltage)
print("Input current: ", power.inCurrent)
print("Output voltage: ", power.outVoltage)
print("Output current: ", power.outCurrent)

print("\nTesting MPPT Status Measurement Parsing")
print("----------------------------------------")

frame = bytearray([6, 3, 1, 206, 207, 0, 0, 0])
print("The expected values are as follows:")
print("Mode: ", 6)
print("Fault: ", 3)
print("Enabled: ", 1)
print("Ambient temp: ", -50)
print("Heatsink temp:",  -49)

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

# Returns a powerMeasurements object
status = mppt.parseMPPTStatus(frame)

# display results
print("Mode: ", status.mode)
print("Mode name: ", mppt.getModeName(status.mode))
print("Fault: ", status.fault)
print("Fault name: ", mppt.getFaultName(status.fault))
print("Enabled: ", status.enabled)
print("Ambient temp: ", status.ambientTemp)
print("Heatsink temp:",  status.heatsinkTemp)

# ============================== MPPT PARSING =================================
mcu = canLib.MCU()

print("\nTesting MCU Motor Data Parsing")
print("----------------------------------------")
frame = bytearray([0xb8, 0x0b, 0x77, 0x01, 0x60, 0x00, 0x92, 0x2])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

mcuMotorData = mcu.parseMotorData(frame)

print("Values received from parsing function")
print(f"RPM: {mcuMotorData.rpm} rpm")
print(f"MCU Current: {mcuMotorData.mcuCurrent} A")
print(f"MCU Voltage: {mcuMotorData.mcuVoltage} V")

print("MCU Faults")

for i in range(0, 16):
    if mcuMotorData.mcuFaults[i] == 1:
        print(f"Fault {i} : {mcu.getFaultStr(i)}")

print("\nTesting MCU Throttle Data Parsing")
print("----------------------------------------")
frame = bytearray([0x96, 0x88, 0x82, 0x00, 0x05, 0x20, 0x00, 0x00])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

mcuThrottleData = mcu.parseThrottleData(frame)

print("Values received from parsing function")
print(f"Throttle Signal: {mcuThrottleData.mcuThrottle}")
print(f"MCU Temp: {mcuThrottleData.mcuTemp} C")
print(f"Motor Temp: {mcuThrottleData.motorTemp} C")
print(f"Feedback Status: {mcu.getFeedbackStr(mcuThrottleData.controllerStatus.statusFeedback)}")
print(f"Command Status: {mcu.getCommandStr(mcuThrottleData.controllerStatus.statusCmd)}")

print("Status of Switch Signals:")
for i in range (0, 8):
    if mcuThrottleData.swStatus[i] == 1:
        print(f"{mcu.getSwStatusStr(i)}: True")

# ============================== LV PARSING =================================

sensors = canLib.SensorFunctions()

print("\nTesting LV Current Sensor Data Parsing")
print("----------------------------------------")

print("Expected value: -0.125 A")

frame = bytearray([0xbe, 0, 0, 0, 0, 0, 0, 0])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

current = sensors.parseCurrent(frame)

print("Result of parsing function:")
print(f"{current} A")

print("\nTesting LV Voltage Sensor Data Parsing")
print("----------------------------------------")

print("Expected value: 12.05 V")

frame = bytearray([0x41, 0x40, 0xcc, 0xcd, 0, 0, 0, 0])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

voltage = sensors.parseVoltage(frame)

print("Result of parsing function:")
print(f"{voltage} V")

print("\nTesting LV Thermistor Data Parsing")
print("----------------------------------------")

print("Expected value: 72.01 F")

frame = bytearray([0x42, 0x90, 0x05, 0x1f, 0, 0, 0, 0])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

temp = sensors.parseTemp(frame)

print("Result of parsing function:")
print(f"{temp} F")

print("\nTesting LV GPS Data Parsing")
print("----------------------------------------")

print("Expected value: Lat 40 42.5998, Long: 74 00.4853")

frame = bytearray([0x45, 0x7c, 0xa9, 0x99, 0x45, 0xe7, 0x43, 0xe2])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

gps = sensors.parseGPS(frame)

print("Result of parsing function:")
print("Lat: ", gps.num1)
print("Long: ", gps.num2)
