import sys
sys.path.append('./build')
import mpptpy # my mppt parsing library

mppt = mpptpy.MPPT()

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
