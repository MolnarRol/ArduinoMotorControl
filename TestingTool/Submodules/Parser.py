def isCommand( checkedString ):
    if len(checkedString) != 0 and checkedString[0] != "#":
        return 1
    return 0

def formatLine( line ):
    split = line.split()
    formated = ""
    for word in split:
        formated += ( word + " " )
    formated = formated[:-1]
    return formated