#!/usr/bin/env bash 

# reading lines 
# see help read (read is a bash builtin)
cat ./data.txt | while read line; do
  echo $line
done

# variables (no spaces so the variable is not read as a command) 
NAME="Jackson"
echo $NAME
echo "$NAME"
echo "${NAME}"

# string quotes 
echo "a double quoted string"
echo 'a single quoted string'

# command substitution (shell execution or function call)
echo "currently in: $(pwd)"
echo "current date: `date`"

# functions are executed in the current shell process
f1(){
  echo "functions are defined with name, parentheses and braces, then called with name and args separated by spaces"
}
f1
echo "Substituting function output: $(f1)"

# conditionals need to use the correct spacing, e.g. there is a space after if and before the test
# also there is a space between the test square braces and the internal contents
# note the semicolon then after each test
# note the if statement closes with fi
# [ is an alias for test command, and ] indicates the end of the expression
# [[ (followed by ]]) is a bash built in which can replace the external call to test
s="my string"
if [ -s "$s" ]; then 
  echo "string is empty"
elif [ -n "$s" ]; then 
  echo "string is not empty"
fi

# brace expansion 
echo {A,B}.sh
echo {A,B}
echo {1..10}

# globbing (filename expansion)
echo * 

# for loops 
for i in ./*.sh; do
  echo $i
done

for i in {1..5}; do
  echo $i
done

# while loops 
i=0
while [ "$i" -lt 10 ]; do
  echo $i
  i=$((i+1))
done

