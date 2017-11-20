#!/bin/bash

#normally processes have 3 files open : stdin (0), stdout (1), stderr (2)
#command > stdout-here 2> stderr-here < stdin-from-here
#command &> file stdout-and-stderr-here
#any > will create new file or overwrite
#the pipe | sends stdout from one command to stdin of another
#command1 2>&1 | command2, sends stdout (1) and stderr (2) to next command's input 
#command |& command2 alternative to send stdout and stderr to next command's stdin
#command >> output appends to a file (create or append)
#command &>> file appends stdout and stderr
#<< here document (embed input for standard inputi)

#sort <<END
#c
#b
#a
#o
#END 

#file descriptors
#exec N< myfile #opens file descriptor N (some number) for reading from myfile
#exec N> myfile #opens file descriptor N (some number) for writing to myfile
#exec N<> myfile #opens file descriptor N (some number) for reading and writing myfile
#exec N>&- or exec N<&- close a file descriptor
#lsof lists files open by all processes, use -p $$ to filter by current process id

#sends stdout to file, errors show on stderr (console)
echo Just '>' ---------------------------------------
find /etc -name grub >grub.out

#sends stderr to file, stdout shows (console)
echo Doing '2>' ---------------------------------------
find /etc -name grub 2>errs.out

#both stdout and stderr to file
echo Doing '&>' ---------------------------------------
find /etc -name grub &>both.out
