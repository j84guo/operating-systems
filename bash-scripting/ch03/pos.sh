#!/bin/bash

# multi digit positional parameters whould be in curly braces
# $0 is the path to the script itself
# shift moves $2 to $1 and $3 to $2
# it can be helpful to use {} for variable name and string concatenation, e.g. echo ${abc}DEF

#let x=abc
#abc=def
#echo ${!x} produces def! this is known as indirection (like dereferencing) 

echo arg1 is $1 arg 11 is ${11}
shift
echo now arg1 is $1 arg 11 is ${11}
echo program is $0

