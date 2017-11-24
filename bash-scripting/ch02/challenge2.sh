#!/bin/bash

#go to directory
cd /usr/bin

#loop through files
for i in *
do

#if is file
if [[ -f $i ]]
then
     #contains string
     if
     strings $i | grep -q "unable to fork"
     then
         echo $i has \"unable to fork\" in it
     fi
fi
done

