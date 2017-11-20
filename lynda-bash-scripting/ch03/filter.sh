# !/bin/bash

# filters read from standard in and write to standard out
# can be used in pipes to process data

# head and tail print first and last n lines that they got from stdin
ls -l | head -3
ls -l | tail -3

# wc counts words, lines and chars
ls | wc -l   


for i in {1..100}
do
	read a b c d e <<END
	$(date)
END
	echo $d >> output
	sleep 1
done

#tail -n2
