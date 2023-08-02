import serial
from time import sleep
from SimpleTool import MSG_DEADTIME


serialPort = serial.Serial()

def serialSetup( com_port ):
    global serialPort
    serialPort.port = com_port
    serialPort.baudrate = 115200
    serialPort.timeout = 0.1

    # Open serial communication
    if serialPort.isOpen():
        serialPort.close()
    serialPort.open()

def getResponse_BLOCKING():
    res = serialPort.read(1024)
    res = res.decode()
    while isResponse( res ) == 0:
        res = serialPort.readline()
        res = res.decode()
    return res

def getByteResponse_BLOCKING():
    res = serialPort.readline()
    while isResponse( res ) == 0:
        res = serialPort.readline()
    return res

def isResponse( data ):
    if len( data ) == 0:
        return False
    return True

def sendCommand( commandString ):

    if commandString == '':
        return ''
    
    serialPort.write( commandString.encode('ascii') )
    sleep( MSG_DEADTIME )
    return getResponse_BLOCKING()