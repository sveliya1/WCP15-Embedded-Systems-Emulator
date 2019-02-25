import json
import sys
import re

json_file = open("commandsJSON.json")   
json_str = json_file.read()             #convert the file into a string
json_data = json.loads(json_str)        #convert the string into a dict, by loading the json data
assemblyList = []
for x in json_data:
  assemblyList.append(x.lower())
assembly_file = open("timing_demo.txt", "r")
interprettedFile = open("parsed.cpp","w")
interprettedFile.write("#include <stdint.h>\n#include <stdio.h>\n#include <iostream>\n#include \"memorymap.h\"\n#ifdef _WIN32\n#include <windows.h>\n#endif\n#define DEBUG 1\n")
interprettedFile.write("uint8_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16;\n")
interprettedFile.write("int result = 0;\n")
interprettedFile.write("int Memory[2048];\n")
interprettedFile.write("void filler(){\ngoto main;")
for line in assembly_file:
	line = line.replace("{","")
	line = line.replace("}","")
	if(len(line.split()) <= 1):
		continue;
	else:
		if(":" in line.split()[0]):
			interprettedFile.write(line.split()[0] + "  ;\n")
	if("<" in line.split()[1]):
		interprettedFile.write("}\nvoid " + line.split()[1].replace("<","").replace(">:","") + "() \n{")
		continue;
	line = line.replace("[","")
	line = line.replace("]","")
	toWrite = ""
	commandFound = 0
	line = line.replace(";"," ;")
	line = line.replace("\n"," ;")
	for i in range(len(line.split())):	
		if(commandFound == 0):
			if(line.split()[i] in assemblyList):
				commandFound = 1
				toWrite += line.split()[i].upper() + "(";
		elif(commandFound == 1):
			if(";" in line.split()[i]):
				commandFound = 2
				continue;
			else:
				if("(" in line.split()[i]):
					toWrite += "\"" + line.split()[i] + " " + line.split()[i+1]+ "\""
					break;
				elif("r" in line.split()[i]):
					toWrite += line.split()[i] + " "
				elif("#" in line.split()[i]):
					toWrite += line.split()[i].replace("#","")+","
				else:
					toWrite += "\"" + line.split()[i].replace(",","") + "\", "
	if(toWrite != ""):
		interprettedFile.write(toWrite[:-1] + ");")
		interprettedFile.write("//" + line + "\n")
	else:
		interprettedFile.write("//Could not parse: " + line + "\n")
				
#interprettedFile.write("}")
interprettedFile.close()
json_file.close()
assembly_file.close()


#def getReplaceValue(toReplace,originalSplit):
#    toReplaceOriginal = toReplace
# #   try:
#    if("ADDRESS" in toReplace):
#        toReplace = re.sub('[^0-9a-zA-Z]',"",originalSplit[0])
#    elif("FUNCTION" in toReplace):
#        for subString in originalSplit:
#            if "<" in subString:
#                toReplace = re.sub("<","",subString)
#                toReplace = re.sub(">","",toReplace)
#                toReplace += "()"
#    elif("A" in toReplace):
#        index = toReplace.replace("A","")
#        toReplace = re.sub('[^0-9a-zA-Z]',"",originalSplit[int(re.sub('[^0-9]','',index)) + 2])
#    elif("S" in toReplace):
#        toReplace = toReplace.replace("S","")
#        toAddValues = map(int, toReplace.split("_"))
#        total = "("
#        for index in toAddValues:
#            index = index + 1
#            #= re.sub(r'([^\s\w]|_)+', ' ', line)
#            totalString = originalSplit[(int)(index)]
#            if("pc" in totalString):
#                total = total +str(int(re.sub('[^\w]','',originalSplit[0]),16))
#            else:
#                if("r" in originalSplit[index]):
#                    total = total + (re.sub('[^0-9a-zA-Z]','',originalSplit[index]))
#                else:
#                    total = total + (re.sub('[^0-9]','',totalString))
#            total += "+"
#        total += "0)"   #this is a bad solution to the code leaving a trailing + at the end of the string
#        toReplace = (total)
##    except:#failed to parse for any reason
#        #toReplace = toReplaceOriginal
#    return str(toReplace) + " "




#json_file = open("commandsJSON.json")   
#json_str = json_file.read()             #convert the file into a string
#json_data = json.loads(json_str)        #convert the string into a dict, by loading the json data.
#assembly_file = open("timing_demo.txt", "r")
#interprettedFile = open("parsed.c","w")
#interprettedFile.write("#include <stdint.h>\n#include <stdio.h>\n#include <iostream>\n#include \"memorymap.h\"\n#ifdef _WIN32\n#include <windows.h>\n#endif\n#define DEBUG 1\n")
#interprettedFile.write("uint8_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16;\n")
#interprettedFile.write("int result = 0;\n")
#interprettedFile.write("int Memory[2048];\n")
#interprettedFile.write("void filler(){\ngoto main;")
#for line in assembly_file:
#    #try:
#        #lineAlphaNumeric = re.sub(r'([^\s\w]|_)+', ' ', line) #remove
#        #non-alphanumeric/space characters
#        #splitValues = lineAlphaNumeric.split()
#        splitValues = line.split()
#        if(len(splitValues) <= 1):
#            interprettedFile.write("\n") 
#            continue
#        if("<" not in splitValues[1]):
#            interprettedFile.write(splitValues[0]+" \n")
#        # Detect Function Header Format: <Function_Header>
#        if("<" in splitValues[1]):
#            labelHeader = splitValues[1].replace("<","") 
#            labelHeader = labelHeader.replace(">:","")
#            labelHeader = "}\nvoid " + labelHeader + "() {"
#            interprettedFile.write(labelHeader)
#            interprettedFile.write("\n")
#        elif(len(splitValues) < 3):
#            interprettedFile.write("// could not parse: " + line)
#        elif(splitValues[2].upper() in json_data):
#            assemblyToCSplit = json_data.get(splitValues[2].upper()).split()
#            #assemblyToC = assemblyToCSplit[0]+": \n"
#            assemblyToC = "\t"
#            #assemblyToC = splitValues[2] + " "
            
#            for toParse in assemblyToCSplit:
#                assemblyToC += getReplaceValue(toParse,splitValues)
#            #if(len(splitValues) >= 4):
#            #    assemblyToC = assemblyToC.replace('A1',splitValues[3])
#            #if(len(splitValues) >= 5):
#            #    if(splitValues[4].contains("#")):
#            #        assemblyToC =
#            #        assemblyToC.replace('A2',splitValues[3].replace("#",""))
#            #    else:
#            #        assemblyToC = assemblyToC.replace('A2',splitValues[3])
#            interprettedFile.write(assemblyToC)
#            interprettedFile.write("//" + line)
#        elif(len(splitValues) < 4):
#            interprettedFile.write("// could not parse: " + line)
#        elif(splitValues[3].upper() in json_data):
#            assemblyToCSplit = json_data.get(splitValues[3].upper()).split()
#            assemblyToC = "\t"
#            #assemblyToC = splitValues[2] + " "
#            for toParse in assemblyToCSplit:
#                assemblyToC += getReplaceValue(toParse,splitValues)
#            #if(len(splitValues) >= 4):
#            #    assemblyToC = assemblyToC.replace('A1',splitValues[3])
#            #if(len(splitValues) >= 5):
#            #    if(splitValues[4].contains("#")):
#            #        assemblyToC =
#            #        assemblyToC.replace('A2',splitValues[3].replace("#",""))
#            #    else:
#            #        assemblyToC = assemblyToC.replace('A2',splitValues[3])
#            interprettedFile.write(assemblyToC)
#            interprettedFile.write("//" + line)
#        else:
#            interprettedFile.write("// could not parse: " + line)
#            #interprettedFile.write("\n")
#    #except:
#     #   interprettedFile.write("// could not parse: " + line)
#interprettedFile.write("}")
#interprettedFile.close()
#json_file.close()
#assembly_file.close()