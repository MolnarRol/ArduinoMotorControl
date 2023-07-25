import sys
import serial
from time import sleep

# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)

def sendCommand( commandString ):
    serialPort.write( commandString.encode() )
    sleep(0.1)

def isCommand( checkedString ):
    if len(checkedString) != 0 and checkedString[0] != "#":
        return 1
    return 0

# Open and read file line by line
# Each line is saved to list
# file = open( sys.argv[1], "r" ).read()
file = open( "test.txt", "r" ).read()       # Testing
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
    baudrate = 115200,
    timeout = None
)
# if serialPort.isOpen():
serialPort.close()
serialPort.open()


for item in commandList:
    if len(item) == 0:                                      # Skip empty lines
        continue
    if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
        sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) )
    else:
        sendCommand(item)
        print(item)

print( "[DONE]" )