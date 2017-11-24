#!/bin/bash

#normal output includes default new line and ignores special characters
echo Hello World

#n flag omits default new line
echo -n Good to see you "\n\n"

#printed on same line as above
echo Thanks

#e flag enables special characters, including tabs and new lines
echo -e Hi "\t\t\t" There "\n\n"

#E falg disables special characters (default)
echo -E Bye "\t\t\t" For now "\n\n"
