# MPPT

## Power Measurements - ID: 0 
- byte 0-1: Input voltage
- byte 2-3: Input current
- byte 4-5: Output voltage
- byte 6-7: Output current
\
- Voltage:
    - voltage scale factor = 0.01
    - voltage
- Current:
    - current scale factor = 0.0005
- Calculation:
    - value from CAN frame / scalefactor

## Status - ID: 1
- byte 0: Mode
    - Value: description
    - 0: Constant Input Voltage
    - 1: Constant input Current
    - 2: Minimum Input Current
    - 3: Constant Output Voltage
    - 4: Constant Output Current
    - 5: temperature De-rating
    - 6: Fault
- byte 1: Fault
    - Value: description
    - 0: OK (No Error)
    - 1: Configuration Error
    - 2: Input Over Voltage
    - 3: Output Over Voltage
    - 4: Output Over Current
    - 5: Input Over Current
    - 6: Input Under Current
    - 7: Phase Over Current
    - 8: Fault
- byte 2: Enabled
    - 0: disabled
    - 1: enabled
- byte 3: ambient temp (C)
    - temp +/- 128
- byte 4: heatsink temp (C)
    - heatsink temp +/- 128

## Received Messages - ID: 5-9
- these are for messages that would get transmitted TO the MPPT
- we will not worry about this right now
- note that when testing with current = 8A, the result gives current = 7.9995
- we may need to pay more attention to precision

