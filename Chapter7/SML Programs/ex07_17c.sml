# ###############################################################
# Filename:		ex07_17c.sml
# Author:		Andrew Laing
# Email:		parisianconnections@gmail.com
# Date:			02/06/2017.
# Description:	Read a series of numbers and determine and print
#				the largest number. The first number read indicates
#				how many numbers should be processed.
# ###############################################################
#
# ######## INSTRUCTIONS #########################################
#
# ### Input control variable ####################################
00 +1020		# Read into MAX
# ### Head of Loop to input numbers #############################
01 +2020		# Load MAX into Accumulator
02 +3118		# Subtract COUNT from the Accumulator
03 +4214		# Branch to 14 if Accumulator is zero
04 +1016		# Read into INPUT
# ### Test if INPUT is the largest number entered ###############
05 +2016		# Load INPUT into Accumulator
06 +3117		# Subtract LARGEST from the Accumulator
07 +4110		# Branch to 10 if Accumulator is negative
08 +2016		# Load INPUT into Accumulator
09 +2117		# Store Accumulator into LARGEST
# ### Increment loop counter and return to head of the loop #####
10 +2018		# Load COUNT into Accumulator
11 +3019		# Add INCR to Accumulator
12 +2118 		# Store Accumulator into COUNT
13 +4001		# Branch to 01 ( start of loop )
# ### End of loop ###############################################
14 +1117		# Write LARGEST to terminal
15 +4300		# Halt program
#
# ######## VARIABLES ############################################
#
16 +0000		# Variable INPUT
17 +0000		# Variable LARGEST
18 +0000		# Variable COUNTER value
19 +0001		# Variable INCRement Amount
20 +0000		# Variable MAXimum (control variable to escape loop)
# ######## END OF PROGRAM #######################################