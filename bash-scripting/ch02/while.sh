#!/bin/bash
x=1

while
	((x<10)) #double parentheses used for testing conditions
do
	echo loop $x
	date >date.$x #sends output to file date.$x
	((x=x+1)) #increments x
done

