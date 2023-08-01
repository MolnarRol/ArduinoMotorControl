import sys
from time import sleep

from modules.SerialComm import *
from modules.FileParser import *
from modules.CommandParser import *

# Keyword defines
WAIT_KEYWORD = "WAIT"
WAIT_KEYWORD_LEN = len(WAIT_KEYWORD)
MSG_DEADTIME = 0.001

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
    print("[Parsing OK]")
    input("Press ENTER to start the test ...")
    sys.exit()

    commandList = removeCommentedLines( file )
    
    # Setting up serial communication
    serialSetup( commandList[0] )
    commandList.pop(0)

    # for line in commandList:
    #     print(line)
    # print("######################")
    
    parsed = parseCommands( commandList )
    funList = parsed[0]

    print( getResponse_BLOCKING(), end = "" )
    for action in funList:
        print(action["arg"])
        action["fun"](action["arg"])

    # serialPort.close()
    sys.exit( "[DONE]" )


if __name__ == "__main__":
    try:
        app()
    except KeyboardInterrupt:
        serialPort.close()
        sys.exit( "App closed!" )