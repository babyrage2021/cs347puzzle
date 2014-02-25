#!/bin/bash
rm a
rm *.out
rm *.outalt
echo "removed old crap"
g++ *.cpp -o a
echo "it compiled"
a puzzle1.txt
a puzzle1.txt 1
echo "puzzle1 done"
a puzzle2.txt
a puzzle2.txt 1
echo "puzzle 2 done"
a puzzle3.txt
a puzzle3.txt 1
echo "puzzle 3 done"
a puzzle4.txt
a puzzle4.txt 1
echo "puzzle4 done"