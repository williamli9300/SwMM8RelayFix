import os

def get_file(): # inputs: pulls './quantum.slx'; outputs: list "lines" of file split by line into list.
    if os.path.isfile('./quantum.slx') == False:
        input("File \"quantum.slx\" does not exist! Please ensure that this executable \
is in the same folder as the start list file.\nPlease press \"Enter\" to close this window.")
        sys.exit()
    with open('./quantum.slx', 'r') as f:
        lines = f.read().splitlines()
        f.close()
    print("opening \"./quantum.slx\"...")
    return lines

def edit_relay_lines(l):
    print("processing...")
    isrelay = False
    teamname = ""
    for i in range(len(l)):
        if l[i][0].isnumeric():
            if "relay" in (l[i]).lower():
                isrelay = True
            else:
                isrelay = False
        else:
            if isrelay == True:
                current_line = l[i].split(";")
                if str(current_line[3]) == "0":
                    teamname = str(current_line[6])
                    print("team name: ", teamname)
                else:
                    if str(current_line[4]) != "":
                        current_line[6] = teamname
                        l[i] = ";".join(current_line)
    return l

def write_file(l):
    with open('./quantum.slx', 'w') as f:
        f.writelines("\n".join(l))
    
lines = get_file()
new_lines = edit_relay_lines(lines)
write_file(new_lines)
input("done. press <Enter> to exit.")
