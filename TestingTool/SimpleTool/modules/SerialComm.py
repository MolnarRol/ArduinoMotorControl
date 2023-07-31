import serial
from time import sleep
from SimpleTool import MSG_DEADTIME


serialPort = serial.Serial()

KEYWORDS = (
    "_WAIT_",
    "_LOOP_",
    "_ENDLOOP_"
)

def LOOP( n, funList ):
    return

def WAIT( n ):
    sleep( n )

def isKeyword( word ):
    for KW in KEYWORDS:
        if word == KW:
            return True
    return False

def parseCommands( lineList ):
    funList = []

    for line in lineList:
        tmp_action = {
            "fun" : None,
            "arg" : None
        }
        splittedLine = line.split()
        if isKeyword( splittedLine[0] ) == False:
            tmp_action["fun"] = sendCommand
            tmp_action["arg"] = line
        else:
            tmp_action["fun"] = WAIT
            tmp_action["arg"] = float(splittedLine[1])

        funList.append( tmp_action )
    return funList



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