import os

class TestsHandler:
    
    def __init__( self, MainPath, TestFolder ):
        self.TEST_FOLDER = None
        self.loadedTxt = ""
        self.loadedTest = ""
        self.fileList = []

        FOLDER_DELIMITER = '\\'
        if os.name != 'nt':
            FOLDER_DELIMITER = "/"
        self.TEST_FOLDER = MainPath + FOLDER_DELIMITER + TestFolder
        self.fileList = os.listdir( self.TEST_FOLDER )

    def getTests( self ):       
        return self.fileList

    def loadTest( self, fileName ):
        for file in self.fileList:
            if fileName == file:
                self.loadedTest = file
                self.loadedTxt = open( self.TEST_FOLDER + "\\" + file, "r").read()
                return self.loadedTxt

        print("[File does not exist!]")
        return 0