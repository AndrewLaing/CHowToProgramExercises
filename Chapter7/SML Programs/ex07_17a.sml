# ###############################################################
# Filename:     ex07_17a.sml
# Author:       Andrew Laing
# Email:        parisianconnections@gmail.com
# Date:         01/06/2017.
# Description:  Use a sentinel controlled loop to read 10 positive
#               integers and compute and print their sum.
# ###############################################################
#
# ######## INSTRUCTIONS #########################################
#
# ### Head of the Loop to read in Positive Integers #############
00 +1008        # Read into INPUT
01 +2008        # Load INPUT into Accumulator
# ### If Input was sentinel exit the loop #######################
02 +4106        # Branch to 06 if Accumulator is negative
# ### Otherwise add INPUT to the SUM and return to Head of Loop #
03 +3009        # Add SUM to Accumulator
04 +2109        # Store Accumulator value into SUM
05 +4000        # Branch to 00
# ### Print out result ##########################################
06 +1109        # Write SUM to Terminal
07 +4300        # Halt program
#
# ######## VARIABLES ############################################
#
08 +0000        # Variable INPUT
09 +0000        # Variable SUM
# ######## END OF PROGRAM #######################################