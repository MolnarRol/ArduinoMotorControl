# This tool requires following packages:
#   - Python 2.7 or Python 3.4 and newer
#   - PySerial (https://pyserial.readthedocs.io/en/latest/)

import sys
import os
import serial          
import serial.tools.list_ports      
from time import sleep

def readConfigFile():
    configFile =  open("config.txt", "r").read()
    lines = configFile.split('\n')

    COM_PORT = ""
    BAUD = 0

    for line in lines:
        item = line.split()
        if len(item) == 0:
            continue
        if item[0] == "port" :
            COM_PORT = item[1]
        elif item[0] == "baudrate" :
            BAUD = item[1]
    
    if COM_PORT == "" or BAUD == 0:
        return newConfigFile()
    print( "Config successfully loaded!" )

    return [ COM_PORT, BAUD ]

def newConfigFile():
    print("No config file found! Creating a new file ...")
    print("----------------------------------------------------------------------------------")
    printSerialPorts()
    print("----------------------------------------------------------------------------------")
    COM_PORT = input( "Sellect COM port (name): " )
    BAUD = input("BaudRate [default = 115200]: ")
    if len(BAUD) != 0:
        BAUD = int(BAUD)
    else:
        BAUD = 115200

    with open( "config.txt", "w" ) as configFile:
        configFile.write( "port " + COM_PORT + "\n")
        configFile.write( "baudrate " + str(BAUD) + "\n")
    clearTerminal()
    return [ COM_PORT, BAUD ]

def printSerialPorts():
    COM_PORTS = serial.tools.list_ports.comports(False)
    for port in COM_PORTS:
        print( port.description, end = " ")
        if ( port.description ).find('CH340') != -1 :
            print("[Probably motor controll device]")
        else:
            print()

def clearTerminal():
    if os.name == 'nt':
        _ = os.system('cls')
    else:
        _ = os.system('clear')

def isResponse( data ):
    if len( data ) == 0:
        return False
    return True

def getResponse_BLOCKING():
    res = serialPort.read(1024)
    res = res.decode()
    while isResponse( res ) == 0:
        res = serialPort.readline()
        res = res.decode()
    return res

def sendCommand( commandString ):

    if commandString == '':
        return ''
    
    serialPort.write( commandString.encode('ascii') )
    return getResponse_BLOCKING()

def isCommand( checkedString ):
    if len(checkedString) != 0 and checkedString[0] != "#":
        return 1
    return 0

def formatLine( line ):
    split = line.split()
    formated = ""
    for word in split:
        formated += ( word + " " )
    formated = formated[:-1]
    return formated

# def removeFileComment( txtFile ):
#     output = []
#     lines = txtFile.split('\n')
#     for line in lines:
#         currentLine = formatLine( line )
#         if( current[0:2] != "# " ):


#     return output

################################################################################################
# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)

################################################################################################
# Open and read file line by line
# Each line is saved to list
filename = "test.txt"
if len(sys.argv) == 2:
    filename = sys.argv[1]    

# file = open( sys.argv[1], "r" ).read()
try:
    file = open( filename, "r" ).read()       # Testing
except:
    sys.exit( "Could not find file named: \"" + filename + "\"" )

################################################################################################
lines = file.split('\n')
commandList = []
for line in lines:
    if isCommand(line):
        commandList.append(formatLine(line))
COM_PORT = commandList[0]
commandList.pop(0)

################################################################################################
# Reading config file
if os.path.isfile( "./config.txt" ):
    SerialConfig = readConfigFile()
else:
    SerialConfig = newConfigFile()

# Setting up serial communication
serialPort = serial.Serial(
    port = SerialConfig[0],
    baudrate = SerialConfig[1],
    timeout = 0.1               # Leave as is 
)

# Open serial communication

if serialPort.isOpen():
    serialPort.close()
serialPort.open()

###############################################################################################
# TestLoop
try:
    print( getResponse_BLOCKING(), end = "" )
    for item in commandList:
        print( item )
        if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
            sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) )
        else:
            sendCommand(item)

    serialPort.close()
    sys.exit( "[DONE]" )
except KeyboardInterrupt:
    sendCommand("stop")
    serialPort.close()
    print("Serial port closed")