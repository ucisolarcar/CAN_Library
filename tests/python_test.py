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

