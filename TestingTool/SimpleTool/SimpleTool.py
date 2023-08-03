import sys
from modules.SerialComm import *
from modules.FileParser import *
from modules.CommandParser import *

# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)
MSG_DEADTIME = 0.001

    # https://www.datasciencelearner.com/convert-a-byte-array-to-float-in-python/
    # import struct
    # serialSetup("COM6")
    # Bytes = getByteResponse_BLOCKING()
    # float_value = struct.unpack('<f', Bytes)[0]
    # print( float_value )
    # sys.exit()

def app():
    if len(sys.argv) == 2:
        filename = sys.argv[1]    
    else:
        filename = "TestingTool/SimpleTool/test.txt"
        # sys.exit("You need to specify one test file\n\t>> python3 SimpleTool.py <testfile.txt>")

    try:
        file = open( filename, "r" ).read()       # Testing
    except:
        sys.exit( "Could not find file named: \"" + filename + "\"" )

    syntax_errors = syntax_checker( file )
    if len(syntax_errors) != 0:
        for error in syntax_errors:
            print( error )
        sys.exit("Parsing of " + filename + " was unsucsesfull. Stopping the program ...")

    commandList = removeCommentedLines( file )
    
    # Setting up serial communication
    serialSetup( commandList[0] )
    commandList.pop(0)
    
    parsed = parseCommands( commandList )
    funList = parsed[0]

    # print( hex(OP_CODES["start"]) )
    input( "Pres ENTER to start ... " )

    print( getResponse_BLOCKING(), end = "" )
    for action in funList:
        print(action["arg"])
        action["fun"](action["arg"])

    serialPort.close()

    sys.exit( "[DONE]" )


if __name__ == "__main__":
    try:
        app()
    except KeyboardInterrupt:
        serialPort.close()
        sys.exit( "App closed!" )