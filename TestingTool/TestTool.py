import sys
import re
import serial
from time import sleep

# Keyword defines
WAIT_KEYWORD = "WAIT123"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)

# Open and read file line by line
# Each line is saved to list
# file = open( sys.argv[1], "r" ).read()
file = open( "test.txt", "r" ).read()       # Testing
commandList = file.split('\n')
COM_PORT = commandList[0]
commandList.pop(0)

# Setting up serial communication
serialPort = serial.Serial()
serialPort.baudrate = 115200
serialPort.port = COM_PORT
serialPort.open()

def sendCommand( commandString ):
    serialPort.write( commandString.encode() )
    # print(serialPort.readline().decode())


for item in commandList:
    if len(item) == 0:                                      # Skip empty lines
        continue
    if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
        sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) )
    else:
        sleep(0.2)
        sendCommand(item)
        print(item)



serialPort.close()