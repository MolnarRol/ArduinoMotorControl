from Submodules.CommandFunctions import *

class CommandClass:
    Commands = []

    def __init__( self, commandList ):
        self.Commands = commandList

    def CommandParser( self, input ):
        for command in self.Commands:
            if command[0] == input:
                command[1]()
                return
        print( "Unknown command \"" + input + "\"" )    