#include <stdlib.h>
#include <stdio.h>

int screenWidth, screenHeight;

void printScreenBorder() {
    char top[screenWidth+1];
    char medium[screenWidth+1];
    char bottom[screenWidth+1];
    char none[screenWidth+1]; 
}

int main(int argc, char *argv[]) {
	
	if (argc < 3) {
        printf("[ERROR] Too few parameters\n");
        exit(0);
    }

    screenWidth = argv[1];
    screenHeight = argv[2];
    
    printScreenBorder();

	return 0;
}
