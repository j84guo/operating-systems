#!/bin/bash

#prompt user
echo -n "Print message? "

#execution flag
valid=0

#while we want to keep looping
while
[ $valid == 0 ]
do
    read ans
    case $ans in
   
    #any of these strings
    yes|YES|y|Y ) echo Will print the message
                  echo The Message
                  valid=1
                  ;;
    #first pattern then second
    [nN][oO]    ) echo Will NOT print the message 
                  valid=1 ;;
    #anything else
    *           ) echo Yes or No of some form please ;;
    esac
done
