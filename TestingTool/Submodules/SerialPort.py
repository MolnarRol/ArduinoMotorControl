import serial 

class SerialPortHandler:

    serialPort = serial.Serial()

    def __init__( self, PORT, BAUD ):
        self.serialPort.port = PORT
        self.serialPort.baudrate = BAUD
        self.serialPort.timeout = 0.1

    def openPort( self ):
        # Open serial communication
        if self.serialPort.isOpen():
            self.serialPort.close()
        self.serialPort.open()

    def closePort( self ):
        self.serialPort.close()

    def sendCommand( self, commandString ):

        if commandString == '':
            return ''
        
        self.serialPort.write( commandString.encode('ascii') )
        return self.getResponse_BLOCKING()

    def getResponse_BLOCKING( self ):
        
        res = self.serialPort.read(1024)
        res = res.decode()
        while self.isResponse( res ) == 0:
            res = self.serialPort.readline()
            res = res.decode()
        return res
    
    def isResponse( self, data ):
        if len( data ) == 0:
            return False
        return True

def printSerialPorts():
        import serial.tools.list_ports 
        COM_PORTS = serial.tools.list_ports.comports(False)
        COM_PORTS_NAME  = []
        for port in COM_PORTS:
            COM_PORTS_NAME.append( port.device )
            print( port.description, end = " ")
            if ( port.description ).find('CH340') != -1 :
                print("[Probably motor controll device]")
            else:
                print()
        return COM_PORTS_NAME