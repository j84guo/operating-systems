#!/usr/bin/env bash

# global regular expression print
# grep reads a file line by line and searches for the pattern
# basic usage: grep "test" grep_tutorial.sh 

# get test data
if ! [[ -f a_file ]]; then
  echo "Downloading test file..."
  curl https://www.uccs.edu/~ahitchco/grep/a_file -o a_file
  echo "...done"
fi  
echo "from a_file..."

echo "searching for \"boo\"..."
grep "boo" a_file

echo "-n for line numbers"
grep -n "boo" a_file

echo "-v for lines without the pattern"
grep -v "boo" a_file

echo "-c for number of lines matching the query"
grep -c "boo" a_file
grep -vc "boo" a_file

echo "-l lists the file names which have lines matching the query"
grep -l "boo" *

echo "-i ignores case"
grep -i "BOO" a_file

echo "-x looks for a line that matches exactly"
grep -x "line exactly matches" a_file

echo "-f points to a file containing the search string"

echo "-w searches for the pattern as a word"
grep -w "boot" a_file

echo "-r searches recursively"
grep -rn "boo" .

