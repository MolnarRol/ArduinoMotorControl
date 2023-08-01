from time import sleep
import modules.SerialComm as SerialComm

KEYWORDS = (
    "_WAIT_",
    "_LOOP_",
    "_ENDLOOP_"
)

KEYWORDS_ARDUINO = (
    "start",
    "stop"
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
            tmp_action["fun"] = SerialComm.sendCommand
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

# def parseCommands( lineList, end_symbol=None ):

#     funList = []    
#     idx = 0
#     LAST_IDX = len( lineList )

#     while idx < LAST_IDX:
#         tmp_action = {
#             "fun" : "",
#             "arg" : ""
#         }   

#         splittedLine = lineList[idx].split()                 # Splitting lines to each words devided by whitespace  
        
#         if end_symbol != None:
#             if splittedLine[0] == end_symbol:
#                 idx += 1
#                 break

#         if isKeyword( splittedLine[0] ) == False:   # Check if line contatins command or keyword
#             tmp_action["fun"] = SerialComm.sendCommand
#             tmp_action["arg"] = lineList[idx]
        
#         else:
#             if splittedLine[0] == "_WAIT_":
#                 tmp_action["fun"] = WAIT
#                 tmp_action["arg"] = float(splittedLine[1])

#             elif splittedLine[0] == "_LOOP_":
#                 tmp_action["fun"] = LOOP
#                 loop = parseCommands( lineList[idx+1:], "_ENDLOOP_" )  # Recursion
#                 tmp_action["arg"] = loop[0]
#                 tmp_action["arg"].append( splittedLine[1] )
#                 idx = idx + loop[1]

#         idx += 1
#         funList.append( tmp_action )
#     return [ funList, idx ]