# ###############################################################
# Filename:		ex07_17b.sml
# Author:		Andrew Laing
# Email:		parisianconnections@gmail.com
# Date:			01/06/2017.
# Description:	Use a counter controlled loop to read seven numbers,
#             	some positive and some negative, and compute and 
#				print their average.
# ###############################################################
#
# ######## INSTRUCTIONS #########################################
#
00 +2020		# Load MAX into accumulator
01 +3118        # Subtract COUNT
02 +4211		# Branch to 11 if Accumulator is zero
03 +1016		# Read into INPUT
04 +2016		# Load INPUT into accumulator
05 +3017		# Add SUM to accumulator
06 +2117 		# Store accumulator into SUM
07 +2018		# Load COUNT into accumulator
08 +3019		# Add INCR to accumulator
09 +2118 		# Store accumulator into COUNT
10 +4000		# Branch to 00
11 +2017		# Load SUM into Accumulator
12 +3220		# Divide Accumulator by MAX to get Average
13 +2117		# Store into SUM
14 +1117		# Write SUM to terminal
15 +4300		# Halt program
#
# ######## VARIABLES ############################################
#
16 +0000		# Variable INPUT
17 +0000		# Variable SUM
18 +0000		# Variable COUNTer value
19 +0001		# Variable INCRement Amount
20 +0007		# Variable MAXimum (control variable to escape loop)
# ######## END OF PROGRAM #######################################