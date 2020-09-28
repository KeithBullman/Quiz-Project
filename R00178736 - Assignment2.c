#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Name: Keith Bullman
// ID: R00178736
// Class: SDH2-A
// Developed in CLion; running code elsewhere may have different results

// NOTE: Following features are NOT working
//  - Answers ARE case-sensitive
//  - Difficulty Level 5 is not working,
//  - As a result, Difficulty Level 6 only works with picking a random difficulty from 1-4
//  - Questions do NOT appear in random order

// Spacing Method
void formatSpacing(){

    printf("\n");
    printf("\n===============");
    printf("\n");

}

// Save Method
void saveFile(int correct, int amount, int difficulty){

    char fileName[] = "quiz_history.txt";

    FILE *file;

    // Write to new file
    file = fopen(fileName, "w");

    // Write relevant data onto new lines (file name, amount of correct answers, amount of questions, score, and difficulty level)
    fprintf(file, "Name of File: %s", fileName);
    fprintf(file, "\nNumber of Correct Answers: %d", correct);
    fprintf(file, "\nTotal Number of Questions: %d", amount);
    fprintf(file, "\nScore: %d / %d", correct, amount);
    fprintf(file, "\nDifficulty Level: %d", difficulty);

    fclose(file);

}

// Generate Hint Based on Difficulty User Chose
void difficultyLevel(int chosenDifficulty, int amount, int arrayCounter, char answers[500][500]){

    // No clue is given, only a "?" is shown
    if(chosenDifficulty == 1){
        printf("?");
    }

    // A set of blank dashes separated by spaces is displayed; one for every letter in the answer
    else if(chosenDifficulty == 2){

        // Create int variable that is the length of the current answer
        int answerLength = strlen(answers[arrayCounter]);

        // Print a dash for each letter in the answer
        for(int i = 0; i < answerLength-1; i++){
            printf("- ");
        }

        // If it is the final question, add another "-" as without it, a 5 letter word will only appear as "- - - -"
        if(arrayCounter == amount - 1) {
            printf("- ");
        }
    }

    // The first and last letters are shown
    else if(chosenDifficulty == 3){

        // Create char variable that is equal to current answer
        char * answer = answers[arrayCounter];

        // Create int variable that stores length of current answer
        int answerLength = strlen(answer);

        //If it's the last question in array
        //This is required, otherwise the final question hint will print incorrectly
        //Without this, the hint Paris (P - - - s) would print as (P - - i) if it was the last question in the array
        if(arrayCounter == amount - 1) {

            for (int i = 0; i < answerLength; i++) {

                //Print the letter where i is equal to either randomly generated number
                if (i == 0 || i == answerLength-1) {
                    printf("%c ", answer[i]);
                }

                    //Otherwise print a dash
                else {
                    printf("- ");
                }
            }
        }

        //If it's not the last question in the array
        else {
            // For loop to print each beginning/ending of word and dashes in other spots
            for (int i = 0; i < answerLength - 1; i++) {

                // If index is at beginning or end of answer, print letter instead of dash
                if ((i == 0) || (i == (answerLength - 2))) {
                    printf("%c ", answer[i]);
                }

                    // Otherwise, print dash
                else {
                    printf("- ");
                }
            }
        }
    }

    // Two random letters from the answer are shown in their correct position
    else if (chosenDifficulty == 4){

        //Generate random seed
        srand(time(0));

        char * answer = answers[arrayCounter];

        int count = 1;

        int lower = 0;

        int upper = strlen(answer);

        int answerLength = strlen(answer);

        int random1 = (rand() % ((upper - 2) - lower + 1)) + lower;

        int random2 = (rand() % ((upper - 2) - lower + 1)) + lower;

        // Infinite while loop until random1 and random2 are not equal
        while(1) {

            //If both the randomly generated numbers are the same, make a new random2
            if (random1 == random2) {
                random2 = (rand() % ((upper - 2) - lower + 1)) + lower;
            }

            //Break out of loop as soon as random1 and random2 are not equal
            else{
                break;
            }

        }

        //If it's the last question in array
        if(arrayCounter == amount - 1) {

            for (int i = 0; i < answerLength; i++) {

                //Print the letter where i is equal to either randomly generated number
                if (i == random1 || i == random2) {
                    printf("%c ", answer[i]);
                }

                //Otherwise print a dash
                else {
                    printf("- ");
                }
            }
        }

        //If it's any other question in array
        else{
            for (int i = 0; i < answerLength - 1; i++) {

                // If i is random1 or random2, print letter
                if (i == random1 || i == random2) {
                    printf("%c ", answer[i]);
                }

                //Otherwise, print dash
                else {
                    printf("- ");
                }
            }
        }
    }

//    else if (chosenDifficulty == 5){
//
//    }

    else if (chosenDifficulty == 6){

        srand(time(0));

        //Random number between 1-4
        int newDifficulty = (rand() % ((4 - 1) - 0 + 1)) + 1;

        //Call method again with new difficulty
        difficultyLevel(newDifficulty, amount, arrayCounter, answers);

    }
}

// Print Questions, Get Answers, Store Correct Answers, and Store Score
void questionTest(int difficulty, int amount, char questions[500][500], char answers[500][500]){

    printf("\nNumber of Questions in Quiz: %d", amount);

    printf("\n");

    // Create arrays for correctQuestions and correctAnswers, for storing data on questions user answers incorrectly
    char correctQuestions[500][500];
    char correctAnswers[500][500];

    char userAnswer[50];

    // While loop counter
    int counter = 0;

    // Correct answers counter
    int correct = 0;

    // Counter for using as an index for printing correct answers to questions user previously answered incorrectly
    int correctCounter = 0;

    // While loop to print all questions and get answers for each question
    while(counter < amount){

        printf("\nQuestion #%d: ", counter+1);
        printf("%s?", questions[counter]);
        printf("\nHINT: ");
        difficultyLevel(difficulty, amount, counter, answers);

        printf("\nAnswer: ");
        scanf("%s", userAnswer);

        char * currentAnswer = answers[counter];

        //Remove the \n from end of answer to ensure it can be correct with userAnswer
        strtok(currentAnswer, "\n");

        // If the comparison between the userAnswer, and the currentAnswer is 0, they are identical
        // If identical, add point to correct
        if(strcmp(userAnswer, currentAnswer) == 0){
            printf("\nCorrect! +1 Point");
            printf("\n");
            correct++;
        }

        // Otherwise, store question and answer in arrays to be called if user wants to view correct answers to questions they previously answered incorrectly
        else{
            printf("\nIncorrect! No points awarded");
            printf("\n");
            strcpy(correctQuestions[correctCounter], questions[counter]);
            strcpy(correctAnswers[correctCounter], answers[counter]);
            correctCounter++;
        }

        // Print score as a fraction
        printf("\nScore: %d/%d", correct, amount);

        // Increment counter
        counter++;

    }

    // Call saveFile method, and pass in amount of correct answers, amount of questions, and difficulty chosen
    saveFile(correct, amount, difficulty);

    printf("\nWould you like to view the correct answers to the questions you answered wrong? (y/n)");

    char yesNo[50];
    printf("\nAnswer: ");
    scanf("%s", yesNo);

    formatSpacing();

    //If user enters y or Y, print list of questions AND correct answers to questions they answered incorrectly with for-loop
    if(strcmp(yesNo, "y") == 0 || strcmp(yesNo, "Y") == 0){
        if(correctCounter == 0){
            printf("\nNo incorrect answers! Good work!");
        }
        else {
            for (int i = 0; i < correctCounter; i++) {
                printf("\nQuestion: %s?", correctQuestions[i]);
                printf("\nCorrect Answer: %s", correctAnswers[i]);
                printf("\n");
            }
        }
    }

    formatSpacing();

    printf("\nThanks for Playing!");

}

// Get fileName, and load file data into question and answer arrays
void loadFile(int userDifficulty) {

    int difficulty = userDifficulty;

    char fileName[500];

    printf("\nEnter filename (case-sensitive): ");
    scanf("%s", fileName);
    printf("\nLoading File...");

    // Create arrays for questions and answers that will store data from text file
    char questions[500][500];
    char answers[500][500];

    FILE *file;

    // If the file doesn't exist, print an error message and exit
    if((file = fopen(fileName, "r")) == NULL){
        printf("\nError opening file! Exiting program...");
        exit(1);
    }

    // Swapper is used to store questions and answers in their respective arrays
    // If swapper = 0, the line will be stored to the question array
    // If swapper = 1, the line will be stored to the answer array
    int swapper = 0;

    int arrayIndex = 0;

    int questionCounter = 0;

    char line[256];

    while (fgets(line, sizeof(line), file)) {

        char *token = strtok(line, "?");

        while (token != NULL) {

            // Add Question to Question Array
            if (swapper == 0) {
                strcpy(questions[arrayIndex], token);
                token = strtok(NULL, "? ");
                questionCounter++;
                swapper = 1;
            }

            // Add Answer to Answer Array
            if (swapper == 1) {
                strcpy(answers[arrayIndex], token);
                token = strtok(NULL, "? ");
                swapper = 0;
            }

            //Increment arrayIndex
            arrayIndex++;
        }
    }

    fclose(file);

    // Call questionTest method, and pass in the difficulty, questionCounter, array of questions and answers
    questionTest(difficulty, questionCounter, questions, answers);

}

// Get User to Enter Difficulty
void getDifficulty() {

    int userDifficulty;

    printf("\nEnter difficulty (1-6): ");
    scanf("%d", &userDifficulty);

    //Pass userDifficulty into loadFile Method
    loadFile(userDifficulty);

}

// Main
int main() {

    //Call Spacing Method
    formatSpacing();

    //Print Header
    printf("\n~ Quiz Game ~");

    //Call Spacing method
    formatSpacing();

    //Call getDifficulty method
    getDifficulty();

    //Return 0 for main method
    return 0;

}
