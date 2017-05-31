import serial
import time
import csv

#def save(data):
    #with open('thruster_test_.csv', 'wb') as csvfile:
        #filewriter = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
        #filewriter.writerow(['Time', 'PWM', 'Measured Force'])
        #for row in data:
            #filewriter.writerow([row])
def main():
    testEnabled = True
    testRunning = False
    dataList = []
    ser = serial.Serial('/dev/ttyACM1', baudrate=9600, timeout=None)
    if ser is not None:
        print("Found device. Awaiting test start...\n")
        while testEnabled:
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
                    testEnabled = False
                    print('Test finished. Saving...')
                    save(dataList)
                    print("Finished saving.")
                else:
                    print data

if __name__ == "__main__":
    main()
