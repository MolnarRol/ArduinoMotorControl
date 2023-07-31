import sys
from time import sleep

from modules.SerialComm import *
from modules.FileParser import *

# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)
MSG_DEADTIME = 0.2

def app():

    if len(sys.argv) == 2:
        filename = sys.argv[1]    
    else:
        sys.exit("You need to specify one test file\n\tpython3 SimpleTool.py <testfile.txt>")

    try:
        file = open( filename, "r" ).read()       # Testing
    except:
        sys.exit( "Could not find file named: \"" + filename + "\"" )

    commandList = removeCommentedLines( file )
    
    # Setting up serial communication
    serialSetup( commandList[0] )
    commandList.pop(0)
    
    funList = parseCommands( commandList )
    print( funList )


    print( getResponse_BLOCKING(), end = "" )
    for action in funList:
        print( action["arg"] )
        action["fun"](action["arg"])

    serialPort.close()
    sys.exit( "[DONE]" )


if __name__ == "__main__":
    try:
        app()
    except KeyboardInterrupt:
        serialPort.close()
        sys.exit( "App closed!" )