#/usr/bin/env bash

# $_ contains the last argument to the precious command
# ${variable} is just a disambiguation mechanism
echo "last arg: ${_}"

# $(cmd) and `cmd` both run a command and substitute themselves for the command output
echo "Today is $(date). A fine day."
echo "The present working directory is `pwd`"

name="jackson"
echo ${name}

echo $0
