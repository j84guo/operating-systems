#/bin/bash

#in bash

#test and [] are builtins
#[[ ]] double brackets enable extra functionality like && and || instead of -a and -o

#braces {} are used to delimit a variable name and parameter expansion, as well as to create lists of strings for loops {a,b,c}

#(()) double parentheses are used for arithmetic operations, e.g. ((a++))
#() single parentheses can be used for arrays 

((n++))
if
((n>4||$1 == 0))
then
echo n is $n one is $1
else
echo in the else
fi

set -x
((n=2**3 + 5))
((y=n^4))
echo y = $y  # prints 1, why?
((y=n|4))
echo y = $y  # prints 1, why?
((y=n&4))
echo y = $y  # prints 1, why?


