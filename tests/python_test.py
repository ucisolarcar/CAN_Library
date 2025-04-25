import sys
sys.path.append('./build')
import mpptpy

class CanFrame:
    CAN_MAX_DLEN = 8  # Maximum number of data bytes in a CAN frame

    def __init__(self, can_id=0, can_dlc=0, data=None):
        self.can_id = can_id                      # 32-bit CAN ID (int)
        self.can_dlc = can_dlc                    # Data length (0 to 8)
        self.data = data or [0] * self.CAN_MAX_DLEN  # List of bytes (default 0s)

    def __repr__(self):
        return f"CanFrame(can_id=0x{self.can_id:X}, can_dlc={self.can_dlc}, data={self.data[:self.can_dlc]})"


mppt = mpptpy.MPPT()

# manually enter the CAN data
frame = CanFrame()
frame.can_id = 0x200
frame.can_dlc = 8
frame.data = [0xf7, 0x68, 0xc1, 0x81, 0xf6, 0xa0, 0xb1, 0xe0]

print("The expected values are as follows:")
print("Input voltage: ", -22)
print("Input current: ", -7.9995)
print("Output voltage: ", -24)
print("Output current: ", -10)

# display frame
print("\nThis is what the CAN frame looks like")
print(frame)

# parsing the data
print("Parsing the data...")
power = mppt.parsePowerMeasurements(frame.data, 1)

# display results
print("Here are the results:")
print(power)
