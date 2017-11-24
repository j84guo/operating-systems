#!/bin/bash

#functions name a sequence of statements that are executed in a the current bash process, not a new one
function myfunc {
   echo starting myfunc
   return
   echo this will not be executed
}

#call function
myfunc

#capture the output of a function in a variable!
n=$(myfunc)
echo n is $n

#after a process terminates you can fetch the exit code with echo $?
