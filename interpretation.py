import json
import sys
import re

def BLInsert(line, BLIndex):
	for subString in line.split():
		if("<" in subString):
			return subString[1:-1]+"( "
	return "//ERROR PARSING BL "

def createISR():
	includesJSON = ""
	with open("hardware_features.json", 'r') as includeFile: 
		jsonText = includeFile.read()             #convert the file into a string
		includesJson = json.loads(jsonText) 
	ISR = "\nvoid ISR()\n{\nif (INTERRUPT_ENABLE && !PRIMASK) {\n"
	ifStatement = "if("
	for listObj in includesJson:
		toWrite = ""
		if("Condition" in listObj.keys()):
			toWrite += ifStatement + listObj["Condition"] + ") {\n"
			toWrite += listObj["IRQHandler"] + "\n"
			if("Clean_Up" in listObj.keys()):
				toWrite += listObj["Clean_Up"] + "\n}\n"
			ifStatement = "else if(" #Change the if to an else if
		if(toWrite != ""):
			ISR += toWrite
	ISR += "}\n"
	return ISR

def GetIncludes():
	includesJSON = ""
	toReturn = ""
	with open("hardware_features.json", 'r') as includeFile: 
		jsonText = includeFile.read()             #convert the file into a string
		includesJson = json.loads(jsonText)   
	for listObj in includesJson:
		toReturn += "#include \"" + listObj["Header_file"] + "\"\n"
	return toReturn

def GetThreads():
	includesJSON = ""
	toReturn = ""
	with open("hardware_features.json", 'r') as includeFile: 
		jsonText = includeFile.read()             #convert the file into a string
		includesJson = json.loads(jsonText)   
	for listObj in includesJson:
		toReturn += listObj["Thread Function"] + "\n"
	return toReturn

def BranchInsert(line, BIndex):
	return(" goto label_" + line.split()[BIndex + 1] + " ")
	return "\\ERROR PARSING BRANCH"

def findLine(lineNumber):
	global assemblyContents
	for line in assemblyContents:
		try:
			if(line.split()[0].rstrip(":") == (lineNumber.replace("(",""))):
				return line
		except:
			pass
	return ""

def StartingLocation():
	locationLine = findLine("0").split()
	startingLine = locationLine[8] + locationLine[7] + locationLine[6] + locationLine[5]
	line = findLine((hex(int(startingLine,16)-1)).lstrip("0x").rstrip("L").zfill(8)).split()
	startingFunction = line[1].replace("<","").replace(">","").replace(":","") + "();"
	return startingFunction.lstrip("0")
	
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
			lineNumber = lineSplit[8] + lineSplit[7] + lineSplit[6] + str(hex(int(lineSplit[5], 16)-1)) #TODO grab the right stuff
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
				toWrite += "STMIA(" + line.split()[i+1].replace("!","").upper()
				i = i+2
				regVector = 0b00000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					regVector = regVector + (0b10000000 >> int(line.split()[i].replace('r','').replace(",","")))#-1
					i += 1
				toWrite += "0b" + "{0:0>9b}".format(regVector)
			elif(line.split()[i] == "ldmia"):
				toWrite += "ldmia(" + line.split()[i+1].replace("!","").upper()
				i = i+2
				regVector = 0b00000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					regVector = regVector + (0b10000000 >> int(line.split()[i].replace('r','').replace(",","")))#-1
					i += 1
				toWrite += "0b" + "{0:0>9b}".format(regVector)
			elif(line.split()[i].upper() == "PUSH"):
				toWrite += "PUSH(SP,"
				#toWrite += line.split()[i+1].replace("!","").upper()
				i += 1
				regVector = 0b000000000
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					if("lr" in line.split()[i]):
						regVector = regVector + (0b100000000 >> 8)
						i += 1
					else:
						regVector = regVector + (0b100000000 >> int(line.split()[i].replace('r','').replace(",","")))#-1)
						i += 1
				toWrite += "0b" + "{0:0>10b}".format(regVector)
			elif(line.split()[i].upper() == "POP"):
				toWrite += "POP(SP,"
				i += 1
				regVector = 0b000000000
				pcFound = False
				while(not("]" in line.split()[i]) and not(";" in line.split()[i])):
					if("pc" in line.split()[i]):
						regVector = regVector + (0b100000000 >> 8)
						i += 1
						pcFound = True
					else:
						regVector = regVector + (0b100000000 >> int(line.split()[i].replace('r','').replace(",","")))#-1)
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
					toSet = findLine(line.split()[-3]).split()[-1] + " "
					toWrite = line.split()[3].replace(",","").upper() + " = " + toSet
					addParentheses = False
					argCount += 1
					break;
				elif("<" in line.split()[i]):
					toWrite += "\"" + line.split()[i] + "\" ";
					argCount += 1
				elif("#" in line.split()[i]):
					toWrite += line.split()[i].replace("#","").replace("[","").replace("]","").upper() +","
					argCount += 1
				elif("r" or "pc" in line.split()[i]):
					toWrite += line.split()[i].replace("[","").replace("]","").upper() + " "
					argCount += 1
				else:
					toWrite += "\"" + line.split()[i].replace(",","").upper() + "\", "
					argCount += 1
	if(toWrite != ""):
		if(toWrite[-1] == ","):
			toWrite = toWrite[:-1]
		toWrite = toWrite.replace("*insertNumber*", str(argCount))
		if(addParentheses):
			interprettedFile.write(toWrite + ");")
		else:
			interprettedFile.write(toWrite + ";")	
		interprettedFile.write("//" + line + "\n")
	else:
		interprettedFile.write("//Could not parse: " + line + "\n")
				
interprettedFile.write("}")
interprettedFile.close()

head = open("head.txt","r").read()
with open("parsed.cpp", 'r+') as interprettedFile:
		content = interprettedFile.read()
		interprettedFile.seek(0)
		
		interprettedFile.write("#include <stdio.h>\n#include <math.h>\n#include <iostream>\n#include <thread>\n#include <mutex>\n#include \"memorymap.h\"\n#include \"flash.h\"\n#include \"macros.h\"\n#include \"IO_Register.h\"\n#ifdef _WIN32\n#include <windows.h>\n#endif\n#include <chrono>\n")
		interprettedFile.write(GetIncludes())
		interprettedFile.write(functionDec)
		
		interprettedFile.write("void ISR();")
		#interprettedFile.write("\nvoid ISR()\n{\n")
		interprettedFile.write(createISR())
		#interprettedFile.write(GetISR())
		#interprettedFile.write("}\n")
		interprettedFile.write(head)
		threads = GetThreads()
		threads = threads + "std::thread last_hope(set_init_clock);\n"
		interprettedFile.write("void main()\n{\nstd::cout << \"Hello\" << std::endl;\nmap->addDevice(flash);\nmap->addDevice(ram);\nmap->addDevice(aips);\nmap->addDevice(gpio);\nmap->addDevice(private_peri);\nburn_flash_to_mem(flash);\nstd::cout << \"Memory Allocate is good\" << std::endl;\nSP = init_sp();\nstart = std::chrono::high_resolution_clock::now();\n" + threads)
		interprettedFile.write(StartingLocation() + "\n")

		#interprettedFile.write("uint64_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, LR, pc, result;\n")
		#interprettedFile.write("bool V_flag =  false;\n")
		#interprettedFile.write("bool C_flag =  false;\n")
		#interprettedFile.write("bool Z_flag=  false;\n")
		#interprettedFile.write("bool N_flag =  false;\n")
		#interprettedFile.write("uint64_t g_cycle_count = 0;\n")
		#
		#interprettedFile.write("\nvoid main()\n{\n")
		#interprettedFile.write(startName)
		interprettedFile.write(content)
json_file.close()
assembly_file.close()