#!/bin/bash

#function
function f {
    
    #private to function
    typeset A
    A=1
}

A=2

#function doesn't affect shell variable
f

echo after f, A = $A
