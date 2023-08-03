OP_CODES = {
    "start"     : 0x10,
    "stop"      : 0x11,
    "mode"      : 0x12,
    "rpm"       : 0x13,
    "duty"      : 0x14,

    "brake on"  : 0x20,
    "brake off" : 0x21,

    "cw"        : 0x30,
    "ccw"       : 0x31,
    "chDir"     : 0x32
}

def isKeyword( word ):
    return

def error_line_formatter( line_num, msg, line ):
    return "[Parsing error] " + msg + "\n| " + str(line_num + 1) + " | " + line + '\n'

def syntax_checker( input ):
    lines = input.split('\n')

    errors = []

    loop_counter = 0

    for idx,line in enumerate(lines):
        stripped = line.strip()
        splitted = stripped.split()
        n_splitted = len(splitted)

        if n_splitted == 0:
            continue
        elif splitted[0][0] == '#':
            continue

        if n_splitted > 2:
            errors.append( error_line_formatter( idx, "Too many commands/parameters were inputted!", line ) )
            continue

        match splitted[0]:
            case "_LOOP_":
                if n_splitted == 1:
                    errors.append( error_line_formatter( idx, "No number of iteration of the LOOP was provided!", line ) )
                else:
                    if splitted[1].isdigit():
                        iterations = int(splitted[1])
                        if iterations < 1:
                            errors.append( error_line_formatter( idx, "Invalid number of iterations. LOOP <n> where n >= 1", line ) )
                    else:
                        errors.append( error_line_formatter( idx, "Iteratior in not a number!", line ) )
                        
                    
                loop_counter += 1
            
            case "_ENDLOOP_":
                if n_splitted > 1:
                    errors.append( error_line_formatter( idx, "Unexpected parameter in _ENDLOOP_", line ))
                else:
                    loop_counter -= 1

            case "_WAIT_":
                if n_splitted == 1:
                    errors.append( error_line_formatter( idx, "Wait time not specified!", line ) )
                else:
                    if splitted[1].isdigit():
                        waittime = float(splitted[1] )
                        if waittime <= 0:
                            errors.append( error_line_formatter( idx, "Wait time must be > 0.0!", line ) )
                    else:
                        errors.append( error_line_formatter( idx, "Wait time must contain only numbers", line ) )

            case _:
                continue

        # print( str(idx) + "\t| ", end="" )
        # print( line )
    
    if loop_counter > 0:
        errors.append( "One or more loops were not terminated by \"_ENDLOOP_\"!" )
    elif loop_counter < 0:
        errors.append( "Additional \"_ENDLOOP_\" symbols declared!" )

    return errors