import sys
import re
import serial
from time import sleep

WAIT_KEYWORD = "WAIT123"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)

file = open( "test.txt", "r" ).read()
commandList = file.split('\n')
COM_PORT = commandList[0]
print(COM_PORT)

for item in commandList:
    if item[ 0:WAIT_KEYWORD_LEN ] == WAIT_KEYWORD:
        sleep( float( item[(WAIT_KEYWORD_LEN + 1):] ) )
    else:
        print(item)