#!/bin/bash

# lack of spaces ensures the variable is not mistaken for an executable
count=0

# test arguments 
if [ $# -ne 1 ] ; then 
  echo "usage is $0 <dir>"
  exit 1
fi 

# ensure argument is a directory 
if [ ! -d "$1" ] ; then 
  echo "$1 is not a directory"
  exit 1
fi

# find executable files in directory 
for filename in "$1"/*
do 
  if [ -x "$filenmae" ] ; then 
    echo $filename
    count=$((count+1)) 
  fi
done

echo 
echo "$count executable files found"

exit 0
