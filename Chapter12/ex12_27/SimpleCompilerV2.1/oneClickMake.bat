@echo off
cmd /k gcc -m32 -Wall -g3 -fverbose-asm -g src/IntStack.c src/StringMethods.c src/main.c -o SimpleCompilerV2.1.exe