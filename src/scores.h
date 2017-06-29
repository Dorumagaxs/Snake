typedef struct Score {
	char playerName[10];
	int score;
} Score;

Score getRecord() {
    char readName[10];
    int readScore;
    FILE *scoresFile;
    Score record;

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

Queue* getScores() {
    int i;
    FILE *scoresFile;
    Score *readScore;
    Queue *scores;

    scores = NULL;
    scoresFile = fopen("files/scores", "r");

    if (scoresFile != NULL) {
        scores = newQueue();

        while (!feof(scoresFile)) {
            readScore = (Score*) malloc(sizeof(Score));

            if (readScore != NULL) {
                fscanf(scoresFile, "%s", readScore->playerName);
                fscanf(scoresFile, "%i", &readScore->score);
            }

            enqueue(scores, readScore);
        }
    }

    fclose (scoresFile);

    return scores;
}