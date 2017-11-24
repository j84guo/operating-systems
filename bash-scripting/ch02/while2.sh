#!/bin/bash

#reads lines from command output (piped to while)
ls -l /etc | while
     read a b c d #splits input based on tokens, last variable gets the rest
do
     echo owner is $c
done

