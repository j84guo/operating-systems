#!/bin/bash

#loops through list of strings
for i in dog cat hotdog
do
   echo i is $i
done

#loops through integers (seq outputs an inclusive list of integers on different lines)
#note the back ticks which substitutes command output, synonymous to $()
for i in `seq 3 5`
do
    echo i in seq is $i
done

#loops through alphabet sequence
#bash knows about certain sequences, such as letters, integers
for i in {N..P}
do
    echo i in letter list is $i
done

#loop through each line in data file
#$() captures output, <data_file fetches file content (like cat)
for d in $(<data_file)
do
     echo d in data_file is $d
done

#bash file globbing finds shell scripts in current directory
#output file names
for j in *.sh
do
   echo $j
done

#output of find command (recursively search starting from current directory)
for f in $(find /etc 2>/dev/null | grep grub)
do
     echo grub named things are $f 
done


