#!/bin/bash

#initialize x and y
x=01
y=1

echo comparing $x and $y

#string compare fails
if
[ $x == $y ]
then
   echo ==
else
   echo not ==
fi

#test numeric  equality
if
[ $x -eq $y ]
then
   echo eq 
else
   echo not eq 
fi

#== checks numeric equality
if
((x==y))
then
   echo '(())' ==
else
   echo not '(())' ==
fi


