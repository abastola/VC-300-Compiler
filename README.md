# VC-300-Compiler

The VC-3600 is a decimal computer with 10,000 words of memory. Each word consists of 6 decimal digits. There is an additional word of memory called the accumulator. The machine language instructions for the VC-3600 is of the following form:

                             |2 digits       | 4 digits       | 
                             |operation code | address portion|

A machine language program is a sequence of machine language instructions stored in memory. The computer executes a machine language program by obeying the commands specified by a sequence of instructions stored in successive memory locations. The first instruction of a program is assumed to be at location 100. 

## This repo contains code used to create an assembler and emulator for the VC3600 computer.   
