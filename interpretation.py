import json
import sys

json_file = open("commandsJSON.json")
json_str = json_file.read()
json_data = json.loads(json_str)


assembly_file = open("assignment1_assembly.txt")
interprettedFile = open("parsed.c","w")
for line in assembly_file:
    if(line == "\n"):
        interprettedFile.write("\n")
    else:
        splitValues = line.split(" ")
        if( "<" in splitValues[1]):
            toWrite = splitValues[1].replace("<","")
            toWrite = toWrite.replace(">","")
            interprettedFile.write("Label: " + toWrite)
        elif(len(splitValues)<4):
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")
        elif(splitValues[3].upper() in json_data):
            toWriteLine = json_data.get(splitValues[3].upper())

            interprettedFile.write(toWriteLine)
            interprettedFile.write("//" + line)

        else:
            interprettedFile.write("// could not parse: " + line)

interprettedFile.close()