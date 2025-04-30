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

# ============================== MCU PARSING =================================
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

# ============================== BMS PARSING =================================
bms = canLib.BMS()

print("\nTesting BMS Pack Info data parsing")
print("----------------------------------------")

print("Expected values: current: 50.8A, voltage: 90.6V, \nSOC: 55.5%, Pack Power: 30.8kW")

frame = bytearray([0x01, 0xFC, 0x03, 0x8A, 0x02, 0x2B, 0x01, 0x34])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")
pack_info = bms.parsePackInfo(frame)

print("Results:")
print(f"Pack Current: {pack_info.packCurrent} A")
print(f"Pack Voltage: {pack_info.packVoltage} V")
print(f"Pack SOC: {pack_info.packSOC}%")
print(f"Pack Power: {pack_info.packPower} kW")
print("(You probably have to manually round these values)")

print("\nTesting BMS Temperature Info data parsing")
print("-------------------------------------------")

print("Expected values:\nAvg Temp: 71C\nInternal Temp: 80C\nHighest Temp: 82C\nHighest Temp Thermistor ID: 1\n")

frame = bytearray([0x47, 0x00, 0x50, 0x00, 0x52, 0x00, 0x01, 0x00])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")
temp_info = bms.parseTempInfo(frame)

print("Results:")
print(f"Avg Temp: {temp_info.avgTemp} C")
print(f"Internal Temp: {temp_info.internalTemp} C")
print(f"Highest Temp: {temp_info.highTemp} C")
print(f"Highest Temp Thermistor ID: {temp_info.highTempID}")

print("\nTesting BMS Faults data parsing")
print("-------------------------------------------")

print("Expected faults:\n")
print("----------------------------------------------")
print("Expected Faults:")
print("Current Limit Status: DCL Reduced Due To Low SOC, DCL Reduced Due To Low Cell Voltage")
print("DTC Status #1: P0A07 (Discharge Limit Enforcement Fault), P0A0E (Lowest Cell Voltage Too Low Fault)")
print("DTC Status #2: P0AFA (Low Cell Voltage Fault), P0A06 (Charge Limit Enforcement Fault)")
print("Precharge Status: Precharge waiting for activation (OFF)")

frame = bytearray([0x00, 0x09, 0x00, 0x41, 0x80, 0x08, 0x00, 0x00])

# display frame
print("\nThis is what the CAN frame looks like")
for i in range(0, len(frame)):
    print(f"data[{i}]: 0x{frame[i]:02X}")

# parsing the data
print("\nParsing the data...\n")

bms_faults = bms.parseFaults(frame)

print("Results:")

print("Current Limit Status:")
for i in range(0, 16):
    if bms_faults.currLimitStatus[i] == 1:
        print(f"{bms.getCurrLimitStr(i)}: True")

print("DTC Status #1:")
for i in range(0, 16):
    if bms_faults.dtcFlags1[i] == 1:
        print(f"{bms.getDtcFlag1Str(i)}: True")

print("DTC Status #2:")
for i in range(0, 16):
    if bms_faults.dtcFlags2[i] == 1:
        print(f"{bms.getDtcFlag2Str(i)}: True")

print(f"Precharge State: {bms.getPrechargeStr(bms_faults.prechargeState)}")
