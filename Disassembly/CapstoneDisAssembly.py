#from capstone import *
with open("assignment1.srec","rb") as f:
	CODE = f.read()
md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
with open("Assembly.asm", "w") as wf:
	for i in md.disasm(CODE, 0x0000):
		print("0x%x:\t%s\t%s" %(i.address, i.mnemonic, i.op_str))
		wf.writelines("0x%x:\t%s\t%s \n" %(i.address, i.mnemonic, i.op_str))