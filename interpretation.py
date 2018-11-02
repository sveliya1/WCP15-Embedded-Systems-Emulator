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
            labelHeader = splitValues[1].replace("<","")
            labelHeader = labelHeader.replace(">","")
            interprettedFile.write("Label: " + labelHeader)
        elif(len(splitValues)<4):
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")
        elif(splitValues[3].upper() in json_data):
            assemblyToC = json_data.get(splitValues[3].upper())
            interprettedFile.write(assemblyToC)
            interprettedFile.write("//" + assemblyToC)

        else:
            interprettedFile.write("// could not parse: " + line)

interprettedFile.close()
assembly_file.close()