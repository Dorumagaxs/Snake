int getRecord() {
    int record, readScore;
    FILE *scores;

    record = 0;
    
    scores = fopen("files/scores", "r");
    
    if (scores != NULL) {
        while (!feof(scores)) {
            fscanf(scores, "%i", &readScore);

            if (readScore > record)
                record = readScore;
        }
    }

    fclose(scores); 

    return record;
}

void addNewScore(int newScore) {
    FILE *scores;

    scores = fopen("files/scores", "a");

    if (scores != NULL)
        fprintf(scores, "\n%i", newScore);

    fclose(scores);
}
