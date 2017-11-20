#!/bin/bash
x=abc
abc="Start Of Alphabet"

echo x is $x
echo abc is $abc

#rereferencing x using ${!x}
echo '${!x}' is ${!x}

