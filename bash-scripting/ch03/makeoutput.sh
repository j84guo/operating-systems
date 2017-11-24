#!/bin/bash
for i in {1..100}
do
    read a b c d e <<END
    $(date)
END
    echo $d 
    sleep 1
done

# run the script with ./makeoutput.sh > output &
# to run it in the background and send output to output file
# use tail -n2 -f output to follow the last 2 lines of the output
