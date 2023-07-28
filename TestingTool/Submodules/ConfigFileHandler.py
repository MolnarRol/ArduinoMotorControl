import re
import os

class Config:
    COM_PORT = ""
    BAUD_RATE = 0
    TEST_FOLDER = ""

    def __init__( self ):
        if os.path.isfile( "config.txt" ):
            self.readConfigFile()
        else:
            self.__newConfigFile()

    def readConfigFile( self ):
        configFile =  open("config.txt", "r").read()
        lines = configFile.split('\n')

        for line in lines:
            item = line.split()

            if len(item) == 0:
                continue

            if item[0] == "port" :
                self.COM_PORT = item[1]
            elif item[0] == "baudrate" :
                self.BAUD_RATE = item[1]
            elif item[0] == "testfolder" :
                self.TEST_FOLDER = item[1]

        if self.COM_PORT == "" or self.BAUD_RATE == 0 or self.TEST_FOLDER == "":
            return self.__newConfigFile()
        print( "[Config successfully loaded!]" )

    def __newConfigFile( self ):
        # from TestTool import clearTerminal
        from SerialPort import printSerialPorts

        # clearTerminal()
        print("No config file found! Creating a new file ...")
        print("----------------------------------------------------------------------------------")
        COM_PORTS = printSerialPorts()
        print("----------------------------------------------------------------------------------")
        
        while self.COM_PORT == "" :
            inputted_com = input( "Sellect COM port (name): " ).strip()
            for port in COM_PORTS:
                if inputted_com == port:
                    self.COM_PORT = inputted_com
                    break
            if self.COM_PORT == "":
                print( "No port named \"" + inputted_com + "\" can be accessed!", end = " " )

        while self.BAUD_RATE == 0:
            inputted_baud = input("BaudRate [default = 115200]: ")

            if len( inputted_baud ) != 0:
                if re.match("/^d{4, 6}", inputted_baud) :
                    self.BAUD_RATE = int( inputted_baud )
                else:
                    print( "Bad baud: \"" + inputted_baud + "\"", end = " " )
            else:
                self.BAUD_RATE = 115200

        self.TEST_FOLDER = input( "Specify folder with test files: " ).strip()

        with open( "config.txt", "w" ) as configFile:
            configFile.write( "port " + self.COM_PORT + "\n")
            configFile.write( "baudrate " + str(self.BAUD_RATE) + "\n")
            configFile.write( "testfolder " + self.TEST_FOLDER )
        # clearTerminal()