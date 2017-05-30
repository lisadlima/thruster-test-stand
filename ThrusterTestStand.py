import serial
import time

testRunning = False
ser = serial.Serial('/dev/ttyACM0', baudrate=9600, timeout=None)

if ser is not None:
    print("Found device. Awaiting test start...\n")

    while True:
        data = ser.read()
        time.sleep(1)
        bytesInQ = ser.inWaiting()
        data += ser.read(bytesInQ)

        if data is not "":
            if (data == '$' and not testRunning):
                print('Test started!')
                testRunning = True
            elif (data == '!' and testRunning):
                testRunning = False
                print('Test finished. Saving...')
                # Save
            else:
                print(data)
