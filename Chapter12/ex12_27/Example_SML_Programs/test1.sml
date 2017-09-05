# ###############################################################
# Filename:		test1.sml
# Author:		Andrew Laing
# Email:		parisianconnections@gmail.com
# Date:			30/07/2017.
# Description:	Use a sentinel controlled loop to read 10 positive
#             	integers and compute and print their sum.
#               Enter a negative number as the sentinel
#               Extended simpletron version.
# ###############################################################
#
# ######## INSTRUCTIONS #########################################
#
# ### Head of the Loop to read in Positive Integers #############
00 +100008		# Read into INPUT
01 +200008      # Load INPUT into Accumulator
# ### If Input was sentinel exit the loop #######################
02 +510006		# Branch to 06 if Accumulator is negative
# ### Otherwise add INPUT to the SUM and return to Head of Loop #
03 +300009		# Add SUM to Accumulator
04 +210009		# Store Accumulator value into SUM
05 +500000		# Branch to 00
# ### Print out result ##########################################
06 +110009 	    # Write SUM to Terminal
07 +540000		# Halt program
#
# ######## VARIABLES ############################################
#
08 +000000		# Variable INPUT
09 +000000		# Variable SUM
# ######## END OF PROGRAM #######################################