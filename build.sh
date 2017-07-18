#Create 'binary' folder
if [ ! -d ./binary ]; then
    mkdir ./binary	
fi

#Delete previous compiled file
if [ -f ./binary/Snake ]; then
    rm ./binary/Snake
fi
#Compiles the source code
gcc -pthread -o ./binary/Snake ./src/Snake.c
