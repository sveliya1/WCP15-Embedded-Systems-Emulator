import os
import sys
# Uses Python 3.x
srec_binary = None
# Search directory for .srec file
for file in os.listdir(os.getcwd()):
    if file.endswith(".srec"):
        srec_binary = file
if srec_binary is None:
    print("Unable to find srec file, cannot parse flash")
    sys.exit()
binary_file = open(srec_binary, 'r')
binary_file_text = binary_file.readlines()
binary_file.close()
binary_file_text.pop(0)
binary_file_instructions = []
flash_memory_file = open('flash.cpp', 'w')
flash_memory_file.write("#include \"flash.h\" \n#include \"memorymap.h\" \n \n void burn_flash_to_mem(ROMDevice *flash) { \n")
for line in binary_file_text:
    instruction_address = int(line[4:8],16)
    for i in range(8,len(line)-4,2):
        value = hex(int(line[i:i+2],16))
        # Zero pad address so it is the correct length
        instruction_address = f"{instruction_address:#0{10}x}"
        flash_memory_file.write("\tflash -> programROM((uint32_t) " + instruction_address + ", " + str(value) + ");\n")
        instruction_address = (int(instruction_address,16) + 1)

flash_memory_file.write("}")

# Need to extract SP from .srec
line = binary_file_text[0]
flash_memory_file.write("\n uint32_t init_sp() { \n")
stack_pointer = line[14:16] + line[12:14] + line[10:12] + line[8:10]
flash_memory_file.write("\t return 0x" + stack_pointer + "; \n }")
flash_memory_file.close()