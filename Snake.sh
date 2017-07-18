
#!bin/bash

#Get the size of terminal screen
lines=$(tput lines)
columns=$(tput cols)

#Create 'files' folder
if [ ! -d ./files ]; then
    mkdir ./files
fi

#Create 'scores' file
if [ ! -f ./files/scores ]; then
    touch ./files/scores
fi

#Hide cursor
tput civis
#Set terminal on raw mode
stty raw
#Set terminal to hide user input
stty -echo
#Execute the binary file
./binary/Snake $lines $columns
#Set terminal no cooked -brkint mode
stty cooked -brkint
#Set terminal to echo user input
stty echo
#Unhide cursor
tput cnorm

clear
