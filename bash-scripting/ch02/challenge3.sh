#!/bin/bash

#counter
n=1

#send output of ps to while loop
ps -ly | while

#read 10 columns
read c1 c2 c3 c4 c5 c6 c7 c8 c9 c10
do

    #skip first row
    if ((n>1))
    then
        #add to rss and sz
        #note double parentheses for arithmetic operations 
        ((rss=rss+c8))
        (( sz=sz+c9 ))

        #output
        echo rss=$rss sz=$sz
    fi

#increment
((n++))
done 
