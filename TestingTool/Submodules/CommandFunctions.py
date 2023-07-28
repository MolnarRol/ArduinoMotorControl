import os

def test():
    print( "test" )

def clearTerminal():
    if os.name == 'nt':
        _ = os.system('cls')
    else:
        _ = os.system('clear')

def loadTest():
    print("load")

def showTestFolder():
    print("")

Commands = [
    [ "clear", clearTerminal, 0 ],
    [ "test", test, 1 ],
    [ "load", loadTest, 1 ],
    [ "show", showTestFolder, 1 ]
    ]