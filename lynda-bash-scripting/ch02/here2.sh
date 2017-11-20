#!/bin/bash

sort <<END
cherry
banana
apple
orange
END

while 
read a b c 
do echo a:$a b:$b c:$c
done <<HERE
one two three
a b c d e f g
1 2

HERE
