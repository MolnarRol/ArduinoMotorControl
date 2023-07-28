import os

def test():
    print( "test" )

def clearTerminal():
    if os.name == 'nt':
        _ = os.system('cls')
    else:
        _ = os.system('clear')

def something():
    print( "something" )

def loadTest():
    print("load")

Commands = [
    [ "clear", clearTerminal, 0 ],
    [ "test", test, 1 ],
    [ "so", something, 0 ]
    ]