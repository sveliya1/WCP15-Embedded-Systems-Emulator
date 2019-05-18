# WCP15-Embedded-Systems-Emualtor
WCP15 Embedded Systems Emulator

Developers:

Seth Arnold, sarnold4@binghamton.edu

William Cass, wcass1@binghamton.edu

Dylan Pereiras, dpereir2@binghamton.edu

Noah Markwica, nmarkwi1@binghamton.edu

Shawn Veliyathu, sveliya1@binghamton.edu

Step by Step Procedure:

1) Compile a binary targeted towards the embedded system in the .out format.

2) Use objdump to disassemble the binary and output the assembly instructions into a text file. Enter the following into a terminal: 
arm-none-eabi-objdump -d <filename>.out > <text_filename>.txt
  
  
3) Use objcopy to create a .srec file from the .out file. Enter a following into the terminal:
arm-none-eabi-objcopy -O srec <filename>.out <filename>.srec
  
  
4) Move the .out, .srec, and text file to the same directory with the Python scripts needed for the emulator. 


5) If the binary contains any hardware components, such as a button, LED, or watchdog timer, then a separate C++ header file needs to be written that replicates its functionality. Once that is written, enter the following information into the hardware_features.json file:

The name of the header file

The C++ code to launch the thread

The name of the thread handler

If the the hardware feature utilizes interrupts, include the following information as well

The condition flag of the interrupt

The IRQ Handler to call when serving the interrupt

The code to indicate the interrupt has been served. (e.g. Putting the interrupt flag low)

6) Run the interpretation.py script by entering the following into a terminal:
python interpreation.py This will output a file called parsed.cpp. This file contains all of the assembly instructions interpreted into C++ code.


7) Run the GlobalParser.py script by entering the following into a terminal:
python GlobalParser.py This will output a file called flash.cpp. This contains functions that will initialize the memory map with the information in flash and the initial value of the stack pointer


8) Compile the C++ code. Any C++ compiler can be used to compile the flash.cpp and interpretation.py. Check the compiler’s documentation to see how to compiler code for that specific compiler. The file “parsed.cpp” may contain code from the windows.h library ; therefore, make sure that the compiler supports Windows.For the project, we used the Visual Studios Compiler. To compile the code with the Visual Studios compiler enter the following into the terminal:
cl flash.cpp parsed.cpp -O2. For performance reasons, it is important optimizations are enabled when compiling.

9) The compiler should output a Windows executable called parsed.exe. Launch the executable by clicking on it or type the following into the terminal.
parsed.exe
