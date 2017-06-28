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
    int readScore;
    FILE *scores;
    Record record;

    record.score = 0;
    strcpy(record.playerName, "None");
    
    scores = fopen("files/scores", "r");
    
    if (scores != NULL) {
        while (!feof(scores)) {
        	fscanf(scores, "%s", record.playerName);
            fscanf(scores, "%i", &readScore);

            if (readScore > record.score)
                record.score = readScore;
        }
    }

    fclose(scores); 

    return record;
}

void addNewScore(char playerName[10], int newScore) {
    FILE *scores;

    scores = fopen("files/scores", "a");

    if (scores != NULL)
        fprintf(scores, "\n%s %i", playerName, newScore);

    fclose(scores);
}
