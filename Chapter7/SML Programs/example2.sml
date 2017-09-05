# This program inputs two numbers, determines the smallest
# then prints the result to the terminal.
00 +1009        # Read into A
01 +1010        # Read into B
02 +2009        # Load A into Accumulator
03 +3110        # Subtract B from Accumulator
04 +4107        # Branch to 07 if Accumulator is negative
05 +1109        # Write A to terminal
06 +4300        # Halt program
07 +1110        # Write B to terminal
08 +4300        # Halt program
09 +0000        # Variable A
10 +0000        # Variable B