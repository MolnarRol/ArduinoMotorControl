# This tool requires following packages:
#   - Python 2.7 or Python 3.4 and newer
#   - PySerial (https://pyserial.readthedocs.io/en/latest/)

import sys          
from time import sleep

import Submodules.ToolCommands as ToolCommands
from Submodules.Parser import *
from Submodules.SerialPort import SerialPortHandler as SerialPortHandler
from Submodules.ConfigFileHandler import Config as ConfigHandler

Config = ConfigHandler()                                                            # Reading config file

Serial = SerialPortHandler( Config.COM_PORT, Config.BAUD_RATE )                     # Setting up serial communication
Serial.openPort()                                                                   # Open serial port

IntCommands = ToolCommands.CommandClass( ToolCommands.Commands )                    # Init internal tool commands
ToolCommands.clearTerminal()                                                        # Clear terminal

try:
    while True:
        IntCommands.CommandParser( input(": ") )
except KeyboardInterrupt:
    Serial.sendCommand("stop")
    Serial.closePort()
    exit("[Exitting program...]")

################################################################################################
# Open and read file line by line
# Each line is saved to list

# # Keyword defines
# WAIT_KEYWORD = "WAIT"
# WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)

filename = "Tests/test.txt"
if len(sys.argv) == 2:
    filename = sys.argv[1]    

# file = open( sys.argv[1], "r" ).read()
try:
    file = open( filename, "r" ).read()       # Testing
except:
    sys.exit( "Could not find file named: \"" + filename + "\"" )

# ################################################################################################
lines = file.split('\n')
commandList = []
for line in lines:
    if isCommand(line):
        commandList.append(formatLine(line))
COM_PORT = commandList[0]
commandList.pop(0)
# ###############################################################################################
# # TestLoop
# try:

print( Serial.getResponse_BLOCKING(), end = "" )

for item in commandList:
    print( item )
    if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
        sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) )
    else:
        Serial.sendCommand(item)

Serial.serialPort.close()

sys.exit( "[DONE]" )
# except KeyboardInterrupt:
#     Serial.sendCommand("stop")
#     Serial.serialPort.close()
#     print("Serial port closed")