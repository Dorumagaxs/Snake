typedef struct Coordinate {
    unsigned int x, y;
} Coordinate;

void gotoxy(int x,int y) {
    printf("%c[%d;%df",0x1B,y,x);
}

void printScreenBorder(int width, int height) {
    char line[width+1];
    char noline[width+1];
    int i;


    line[0] = '|';
    noline[0] = '|';
    line[width-1] = '|';
    noline[width-1] = '|';
    line[width] = 0;
    noline[width] = 0;

    for (i=1; i<width-1; i++) {
    	line[i] = '-';
    	noline[i] = ' ';
    }

    gotoxy(1,1);
    printf("%s", line);

    for (i=2; i<5; i++) {
    	gotoxy(1,i);
    	printf("%s", noline);
    }

    gotoxy(1,5);
    printf("%s", line);

    for (i=6; i<height; i++) {
    	gotoxy(1,i);
    	printf("%s", noline);
    }

    gotoxy(1,height);
    printf("%s", line);
}

void clearArea(Coordinate init, Coordinate end) {
    unsigned int x, y;

    for (y=init.y; y<=end.y; y++) {
        gotoxy(init.x, y);

        for (x=init.x; x<=end.x; x++) {
            printf(" ");
        }
    }
}