#!/bin/bash

#makes string lower case
declare -l lstring="ABCdef"

#makes string upper case
declare -u ustring="ABCdef"

#makes string read only
declare -r readonly="A Value"

#declares integer array
declare -a Myarray

#associative array
declare -A Myarray2

echo lstring = $lstring
echo ustring = $ustring
echo readonly = $readonly
readonly="New Value" #error modifying read only
Myarray[2]="Second Value" #set array item
echo 'Myarray[2]= ' ${Myarray[2]}
Myarray2["hotdog"]="baseball" #put in associative array
echo 'Myarray2[hotdog]= ' ${Myarray2["hotdog"]}

