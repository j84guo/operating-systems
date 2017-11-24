#!/bin/bash
function f1 {
   typeset x
   x=7
   y=8
}

function f2 {
   typeset x
   x=77
   y=9
}

x=1
y=2
echo x is $x
echo y is $y
f1
echo x is $x
echo y is $y
f2
echo x is $x
echo y is $y
