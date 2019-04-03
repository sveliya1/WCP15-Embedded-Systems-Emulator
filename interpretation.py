import json
import sys
import re

def BLInsert(line, BLIndex):
	for subString in line.split():
		if("<" in subString):
			return subString[1:-1]+"( "
	return "//ERROR PARSING BL "

def BranchInsert(line, BIndex):
	return(" goto label_" + line.split()[BIndex + 1] + " ")
	return "\\ERROR PARSING BRANCH"

def findLine(lineNumber):
	global assemblyContents
	for line in assemblyContents:
		try:
			if(line.split()[0] == (lineNumber.replace("(","")+":")):
				return line
		except:
			pass
	return ""
	
startName = ""

with open("timing_demo.txt", 'r+') as assemblyFile:
	content = assemblyFile.read()
	assemblyFile.seek(0)
	content = content.replace("main>", "main_thread>")
	assemblyFile.write(content)
	assemblyFile.seek(0)
	nextLine = False
	lineNumber = ""
	for line in assemblyFile:
		if nextLine:
			lineSplit = line.split()
			lineNumber = lineSplit[8] + lineSplit[7] + lineSplit[6] + str(int(lineSplit[5])-1) #TODO grab the right stuff
			break
		elif "InterruptVector" in line:
			nextLine = True 
	assemblyFile.seek(0)
	for line in assemblyFile:
		if len(line.split()) >= 2 and lineNumber in line.split()[0]:
			startName = line.split()[1].replace("<","").replace(">:","")+"();\n"


json_file = open("commandsJSON.json")   
json_str = json_file.read()             #convert the file into a string
json_data = json.loads(json_str)        #convert the string into a dict, by loading the json data
bjson_file = open("branchJSON.json")   
bjson_str = bjson_file.read()             #convert the file into a string
bjson_data = json.loads(bjson_str)        #convert the string into a dict, by loading the json data
assemblyList = []
functionDec = ""
for x in json_data:
  assemblyList.append(x.lower())
#assemblyList.extend(branchesList)
assembly_file = open("timing_demo.txt", "r")
assemblyContents = assembly_file.readlines()
assembly_file.seek(0)
interprettedFile = open("parsed.cpp","w")
addParentheses = True



for line in assembly_file:
	argCount = 0
	line = line.replace("{","")
	line = line.replace(".","");
	line = line.replace("}","")
	if(len(line.split()) <= 1):
		continue;
	else:
		if(":" in line.split()[0]):
			interprettedFile.write("label_" + line.split()[0] + "  ;\n")
	if("<" in line.split()[1]):
		functionDec += "void " + line.split()[1].replace("<","").replace(">:","")+"();\n"
		interprettedFile.write("}\nvoid " + line.split()[1].replace("<","").replace(">:","") + "() \n{")
		continue;
	#line = line.replace("[","")
	#line = line.replace("]","")
	toWrite = ""
	commandFound = 0
	validSinceCheck = 0
	line = line.replace(";"," ;")
	line = line.replace("\n"," ;")
	for i in range(len(line.split())):
		addParentheses = True
		if(commandFound == 0):
			if("bx	lr" in line):
				toWrite = "return "
				addParentheses = False;
				break;
			elif(line.split()[i].upper() in bjson_data.keys()):
				if(line.split()[i] == "bl"):	#fix this
					toWrite += bjson_data[line.split()[i].upper()]
					toWrite += BLInsert(line, i)					
					break
				else:
					toWrite += bjson_data[line.split()[i].upper()]
					toWrite += BranchInsert(line, i) +"; "
					toWrite += "} "
					addParentheses = False;
					break;
			elif(line.split()[i] == "stmia"):
				toWrite += "stmia(" + line.split()[i+1].replace("!","")
				i = i+2
				regVector = 0b00000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					regVector = regVector + (0b10000000 >> int(line.split()[i].replace('r','').replace(",","")))-1
					i += 1
				toWrite += "0b" + "{0:0>9b}".format(regVector)
			elif(line.split()[i] == "ldmia"):
				toWrite += "ldmia(" + line.split()[i+1].replace("!","")
				i = i+2
				regVector = 0b00000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					regVector = regVector + (0b10000000 >> int(line.split()[i].replace('r','').replace(",","")))-1
					i += 1
				toWrite += "0b" + "{0:0>9b}".format(regVector)
			elif(line.split()[i] == "PUSH"):
				toWrite += "PUSH(sp,"
				i += 1
				regVector = 0b000000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					if("lr" in line.split()[i]):
						regVector = regVector + (0b100000000 >> 8)
						i += 1
					else:
						regVector = regVector + (0b100000000 >> int(line.split()[i].replace('r','').replace(",",""))-1)
						i += 1
				toWrite += "0b" + "{0:0>10b}".format(regVector)
			elif(line.split()[i] == "POP"):
				toWrite += "POP("
				i += 1
				regVector = 0b000000000
				pcFound = False
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					if("pc" in line.split()[i]):
						regVector = regVector + (0b100000000 >> 8)
						i += 1
						pcFound = True
					else:
						regVector = regVector + (0b100000000 >> int(line.split()[i].replace('r','').replace(",",""))-1)
						i += 1
				toWrite += "0b" + "{0:0>10b}".format(regVector)
				if(pcFound):
					toWrite += ");\nreturn "
					addParentheses = False	
					break
			if(line.split()[i] in assemblyList):				
				commandFound = 1
				toWrite += line.split()[i].upper() + "_*insertNumber*("
		elif(commandFound == 1):
			if(";" in line.split()[i]):
				commandFound = 2
				continue;
			else:
				if("(" in line.split()[i]):
					toWrite += "\"" + line.split()[i] + " " + line.split()[i+1]+ "\""
					argCount += 1
					break;
				elif("[" in line.split()[i] and "ldr" in line.split() and "pc" in line):
					toSet = findLine(line.split()[-3]).split()[-1]
					toWrite = line.split()[3].replace(",","") + " = " + toSet
					addParentheses = False
					argCount += 1
					break;
				elif("<" in line.split()[i]):
					toWrite += "\"" + line.split()[i] + "\" ";
					argCount += 1
				elif("#" in line.split()[i]):
					toWrite += line.split()[i].replace("#","").replace("[","").replace("]","") +","
					argCount += 1
				elif("r" or "pc" in line.split()[i]):
					toWrite += line.split()[i].replace("[","").replace("]","") + " "
					argCount += 1
				else:
					toWrite += "\"" + line.split()[i].replace(",","") + "\", "
					argCount += 1
	if(toWrite != ""):
		toWrite = toWrite.replace("*insertNumber*", str(argCount))
		if(addParentheses):
			interprettedFile.write(toWrite[:-1] + ");")
		else:
			interprettedFile.write(toWrite[:-1] + ";")	
		interprettedFile.write("//" + line + "\n")
	else:
		interprettedFile.write("//Could not parse: " + line + "\n")
				
interprettedFile.write("}")
interprettedFile.close()
with open("parsed.cpp", 'r+') as interprettedFile:
		content = interprettedFile.read()
		interprettedFile.seek(0)
		interprettedFile.write("#include <stdint.h>\n#include \"macros.h\"\n#include <stdio.h>\n#include <iostream>\n#include \"memorymap.h\"\n#ifdef _WIN32\n#include <windows.h>\n#endif\n#define DEBUG 1\nusing namespace std;\n")
		interprettedFile.write("uint64_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr, pc, result;\n")
		interprettedFile.write("bool V_flag =  false;\n")
		interprettedFile.write("bool C_flag =  false;\n")
		interprettedFile.write("bool Z_flag=  false;\n")
		interprettedFile.write("bool N_flag =  false;\n")
		interprettedFile.write("uint64_t g_cycle_count = 0;\n")
		interprettedFile.write(functionDec)
		interprettedFile.write("\nvoid main()\n{\n")
		interprettedFile.write(startName)
		interprettedFile.write(content)
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