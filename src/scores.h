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
