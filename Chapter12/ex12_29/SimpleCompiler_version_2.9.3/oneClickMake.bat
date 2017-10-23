@echo off
cmd /k gcc -m32 -Wall -g3 -fverbose-asm -g src/ForLoopStack.c src/IntStack.c src/StringMethods.c src/main.c -o SimpleCompiler.exe