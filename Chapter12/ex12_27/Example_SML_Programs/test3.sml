# This program inputs two numbers, raises the first
# to the power of the second, and prints out the result  
# to the terminal.
00 +100007      # Read into A
01 +100008      # Read into B
02 +200007      # Load A into Accumulator
    03 +350008      # Raise A to the power of B
04 +210009      # Store Accumulator value into C
05 +110009      # Write C to terminal
   06 +540000       # Halt program
07 +000000      # Variable A
 08 +000000     # Variable B
09 +000000      # Variable C
