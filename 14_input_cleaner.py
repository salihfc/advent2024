
input_filename = 'input14.txt'


# Check if input file exists
try:
    ## open file with read and write permission
    with open(input_filename, 'r+') as file:
        input_raw = file.read()
        file.seek(0)

        # For each line, remove first 2 characters
        lines = input_raw.split('\n')
        for line in lines:
            line = line[2:]
            ## replace ',' with ' '
            line = line.replace(',', ' ')
            ## replace 'v=' with ''
            line = line.replace('v=', '')
            print(line)
            ## save to same file
            file.write(line + '\n')

        file.truncate()

except FileNotFoundError:
    print(f'Error: {input_filename} not found')
    exit()