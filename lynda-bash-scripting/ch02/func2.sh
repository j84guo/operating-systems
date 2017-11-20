#!/bin/bash
function f2 {
   echo in f2
   
   #exit terminates the curent process! not just function
   #default exit code is 0
   #we can set our own exit code
   exit 2

   echo more in f2
}

echo starting

f2

echo after f2


