import json
import sys

json_file = open("commandsJSON.json")
json_str = json_file.read()
json_data = json.loads(json_str)

assembly_file = open("assignment2_assembly.txt", "r")
interprettedFile = open("parsed.c","w")
for line in assembly_file:
    if(line == "\n"):
        interprettedFile.write("\n")
    else:
        splitValues = line.split()
        if(len(splitValues) == 1):
           continue
        # Detect Function Header Format: <Function_Header>
        if( "<" in splitValues[1]):
            labelHeader = splitValues[1].replace("<","")
            labelHeader = labelHeader.replace(">","")
            interprettedFile.write("Label: " + labelHeader)
            interprettedFile.write("\n")
        elif(len(splitValues)<3):
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")
        #splitValues[2] contains the instruction
        elif(splitValues[2].upper() in json_data):
            assemblyToC = json_data.get(splitValues[2].upper())
            interprettedFile.write(assemblyToC)
            interprettedFile.write("//" + assemblyToC)
            interprettedFile.write("\n")
        else:
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")

interprettedFile.close()
json_file.close()
assembly_file.close()
