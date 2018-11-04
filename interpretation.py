import json
import sys

json_file = open("commandsJSON.json")   
json_str = json_file.read()             #convert the file into a string
json_data = json.loads(json_str)        #convert the string into a dict, by loading the json data.

assembly_file = open("assignment1_assembly.txt")
interprettedFile = open("parsed.c","w")
interprettedFile.write("void main(){\ngoto main;")
for line in assembly_file:
    if(line == "\n"):
        interprettedFile.write("\n")
    else:
        splitValues = line.split(" ")
        if("<" in splitValues[1]):
            toWrite = splitValues[1].replace("<","")
            toWrite = toWrite.replace(">","")
            interprettedFile.write("Label: " + toWrite)
        elif(len(splitValues) < 4):
            interprettedFile.write("// could not parse: " + line)
            interprettedFile.write("\n")
        elif(splitValues[3].upper() in json_data):
            toWriteLine = json_data.get(splitValues[3].upper())
            toWriteLine = toWriteLine.replace('Rd',splitValues[4])
            interprettedFile.write(toWriteLine)
            interprettedFile.write("//" + line)
        else:
            interprettedFile.write("// could not parse: " + line)

interprettedFile.write("}")
interprettedFile.close()