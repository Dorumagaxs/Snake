
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
#Set terminal on raw mode
stty raw
#Set terminal to hide user input
stty -echo
#Execute the binary file
./bin/Snake $lines $columns
#Set terminal no cooked -brkint mode
stty cooked -brkint
#Set terminal to echo user input
stty echo
#Unhide cursor
tput cnorm

clear
