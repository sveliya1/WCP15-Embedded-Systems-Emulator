import json
import sys

json_file = open("commandsJSON.json")   
json_str = json_file.read()             #convert the file into a string
json_data = json.loads(json_str)        #convert the string into a dict, by loading the json data.

assembly_file = open("assignment2_assembly.txt", "r
interprettedFile = open("parsed.c","w")
interprettedFile.write("void main(){\ngoto main;")
for line in assembly_file:
    if(line == "\n"):
        interprettedFile.write("\n")
    else:
        splitValues = line.split()
        if(len(splitValues) == 1):
           continue
        # Detect Function Header Format: <Function_Header>                     
        if("<" in splitValues[1]):
            labelHeader = splitValues[1].replace("<","")
            labelHeader = labelHeader.replace(">","")
            interprettedFile.write("Label: " + labelHeader)
            interprettedFile.write("\n")
        elif(len(splitValues) < 3):
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")
        elif(splitValues[3].upper() in json_data):
            assemblyToC = json_data.get(splitValues[3].upper())
            assemblyToC = assemblyToC.replace('Rd',splitValues[4])
            interprettedFile.write(assemblyToC)
            interprettedFile.write("//" + line)
        else:
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")


interprettedFile.write("}")
interprettedFile.close()
json_file.close()
assembly_file.close()
