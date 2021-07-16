# System_Software
Implementation of an assembler, linker and emulator for a hypothetical processor

Example of using the software after the build: 
```
asembler -o interrupts.o interrupts.s  
asembler -o main.o main.s  
linker -hex -place=ivt@0x0000 -o program.hex interrupts.o main.o  
emulator program.hex  
```

The interrupts.s main.s files are in the Test folder.
