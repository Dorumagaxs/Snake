typedef struct Record {
	char playerName[10];
	int score;
} Record;

typedef struct ScoreNode {
	char *player;
	int value;
	struct ScoreNode *next;
} ScoreNode;

typedef struct ScoreList {
	int size;
	ScoreNode *first, *last;
} ScoreList;

Record getRecord() {
    char readName[10];
    int readScore;
    FILE *scoresFile;
    Record record;

    record.score = 0;
    strcpy(record.playerName, "None");
    
    scoresFile = fopen("files/scores", "r");
    
    if (scoresFile != NULL) {
        while (!feof(scoresFile)) {
        	fscanf(scoresFile, "%s", readName);
            fscanf(scoresFile, "%i", &readScore);

            if (readScore > record.score) {
                strcpy(record.playerName, readName);
                record.score = readScore;
            }
        }
    }

    fclose(scoresFile); 

    return record;
}

void addNewScore(char playerName[10], int newScore) {
    FILE *scoresFile;

    if (newScore > 0) {
        scoresFile = fopen("files/scores", "a");

        if (scoresFile != NULL)
            fprintf(scoresFile, "\n%s %i", playerName, newScore);

        fclose(scoresFile);
    }
}

void getScores() {
    int i;
    FILE scoresFile;
    Queue scores;
}