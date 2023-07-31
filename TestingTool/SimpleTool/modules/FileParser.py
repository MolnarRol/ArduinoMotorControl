def isCommand( checkedString ):
    if len(checkedString) != 0 and checkedString[0] != "#":
        return 1
    return 0

def removeCommentedLines( file ):
    lines = file.split('\n')
    commandList = []
    for line in lines:
        if isCommand(line):
            commandList.append(line.strip())
    return commandList