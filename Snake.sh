
#!bin/bash

#Get the size of terminal screen
lines=$(tput lines)
columns=$(tput cols)

#Delete previous compiled file
rm ./bin/Snake
#Compiles the source code
gcc -pthread -o ./bin/Snake ./src/Snake.c
#Hide cursor
tput civis
#Put terminal on raw mode
stty raw
#Execute the binary file
./bin/Snake $lines $columns
#Put terminal no cooked -brkint mode
stty cooked -brkint
#Unhide cursor
tput cnorm

clear
