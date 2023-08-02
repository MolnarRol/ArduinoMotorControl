KEYWORDS_ARDUINO = (
    "start",
    "stop",
    "duty",
    "mode",
    "rpm",
    "status",
    "ct"
)

def isKeyword( word ):
    return

def error_line_formatter( line_num, msg, line ):
    return "[Parsing error] " + msg + "\n| " + str(line_num + 1) + " | " + line + '\n'

def syntax_checker( input ):
    lines = input.split('\n')
    errors = []

    loop_counter = 0
    end_loop_counter = 0

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
                    iterations = int(splitted[1])
                    if iterations < 0:
                        errors.append( error_line_formatter( idx, "Invalid number of iterations. LOOP <n> where n >= 0", line ) )
                loop_counter += 1
            
            case "_ENDLOOP_":
                end_loop_counter += 1

            # case "_LOOP_":

            case _:
                continue

        # print( str(idx) + "\t| ", end="" )
        # print( line )
    
    if loop_counter > end_loop_counter:
        errors.append( "One or more loops were not terminated by \"_ENDLOOP_\"!" )
    elif loop_counter < end_loop_counter:
        errors.append( "Additional \"_ENDLOOP_\" symbols declared!" )

    return errors