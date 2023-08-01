import serial
from time import sleep
from SimpleTool import MSG_DEADTIME


serialPort = serial.Serial()

KEYWORDS = (
    "_WAIT_",
    "_LOOP_",
    "_ENDLOOP_"
)

def LOOP( input ):
    iterations = int(input[-1])
    actions = input.copy()
    actions.pop(-1)
    for idx in range( iterations ):
        for command in actions:
            print(command)
            command["fun"](command["arg"])
        continue
    return

def WAIT( n ):
    sleep( n )

def isKeyword( word ):
    for KW in KEYWORDS:
        if word == KW:
            return True
    return False

def parseCommands( lineList, end_symbol=None ):

    funList = []    
    idx = 0
    LAST_IDX = len( lineList )

    while idx < LAST_IDX:
        tmp_action = {
            "fun" : "",
            "arg" : ""
        }   

        splittedLine = lineList[idx].split()                 # Splitting lines to each words devided by whitespace  
        
        if end_symbol != None:
            if splittedLine[0] == end_symbol:
                idx += 1
                break

        if isKeyword( splittedLine[0] ) == False:   # Check if line contatins command or keyword
            tmp_action["fun"] = sendCommand
            tmp_action["arg"] = lineList[idx]
        
        else:
            if splittedLine[0] == "_WAIT_":
                tmp_action["fun"] = WAIT
                tmp_action["arg"] = float(splittedLine[1])

            elif splittedLine[0] == "_LOOP_":
                tmp_action["fun"] = LOOP
                loop = parseCommands( lineList[idx+1:], "_ENDLOOP_" )  # Recursion
                tmp_action["arg"] = loop[0]
                tmp_action["arg"].append( splittedLine[1] )
                idx = idx + loop[1]

        idx += 1
        funList.append( tmp_action )
    return [ funList, idx ]


# def parseCommands( lineList, symbol=None ):
#     funList = []

#     for idx, line in enumerate( lineList ):

#         tmp_action = {
#             "fun" : None,
#             "arg" : None
#         }

#         splittedLine = line.split()
#         if symbol != None:
#             if splittedLine[0] == symbol:
#                 return funList

#         if isKeyword( splittedLine[0] ) == False:
#             tmp_action["fun"] = sendCommand
#             tmp_action["arg"] = line

#         else:
#             if splittedLine[0] == "_WAIT_":
#                 tmp_action["fun"] = WAIT
#                 tmp_action["arg"] = float(splittedLine[1])
#             elif splittedLine[0] == "_LOOP_":
#                 # print( lineList[idx+1:] )
#                 tmp_action["fun"] = LOOP
#                 tmp_action["arg"] = parseCommands( lineList[idx+1:], "_ENDLOOP_" )  # Recursion brain melt
#                 tmp_action["arg"].append( splittedLine[1] )
#             else:
#                 continue
    
#         funList.append( tmp_action )

    
#     return funList



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