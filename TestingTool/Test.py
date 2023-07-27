import serial
import time

arduino = serial.Serial(port='COM6',   baudrate=115200, timeout=.1)
arduino.close()
arduino.open()

def isResponse( data ):
    if len( data ) == 0:
        return False
    return True

def getResponse_BLOCKING():
    res = arduino.read(1024)
    res = res.decode()
    while isResponse( res ) == 0:
        res = arduino.readline()
        res = res.decode()
    return res

try:
    print(getResponse_BLOCKING(), end = "")
    while True:
        msg = input()
        if msg != '':        
            arduino.write( msg.encode('ascii') )
            print(getResponse_BLOCKING(), end = "")
except KeyboardInterrupt:
    arduino.close()
    print("Serial port closed")

