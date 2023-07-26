import sys
import serial
from time import sleep

# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)
MSG_DEADTIME = 1

def sendCommand( commandString ):
    serialPort.write( commandString.encode() )
    sleep(MSG_DEADTIME)

def isCommand( checkedString ):
    if len(checkedString) != 0 and checkedString[0] != "#":
        return 1
    return 0

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

lines = file.split('\n')
commandList = []
for line in lines:
    if isCommand(line):
        commandList.append(line)
COM_PORT = commandList[0]
commandList.pop(0)

# Setting up serial communication
serialPort = serial.Serial(
    port = COM_PORT,
    baudrate = 38400,
    timeout = None
)
if serialPort.isOpen():
    serialPort.close()
serialPort.open()

# Execute commands
for item in commandList:
    print( item )
    if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
        sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) - MSG_DEADTIME )
    else:
        sendCommand(item)

serialPort.close()
sys.exit( "[DONE]" )