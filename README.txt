(For program to work, if using CLion, put 'questions.txt' in a subfolder called cmake-build-debug)

Year 2 - Semester 2
Date: 9th May 2020

Specification:

Implement a quiz game engine.
The game engine loads questions and their answers from a file and asks the questions to the user who needsto provide the answer. 
The game can provide clues to the user, with the amount of information provide ddepending on the level of difficulty.

Details
1.The questions and answers are in a file that is provided as a command line argument to the application.
2.In the QnA file each line has a question and its answer. The answers are always one word. The questionalways ends in ‘?’ then there is a space and following that the answer. For example:What is the capital of France? Paris
3.The application takes a second command line argument, a number <10 that represents the difficultylevel.
The program should
•at start–load the questions and answers from the file–print out the number of questions in the quiz
•start asking questions–for each question, display a clue (if available, see below); the user has one attempt only, and theprogram is case insensitive (accepts both lower and upper case answers)–after each question display the number of questions asked and the number of correctly answeredquestions so far. Example:Score: 5/7
•at the end store the results in a filequiz_history.txt by appending to the file one line containing:–name of the quiz file–number of questions answered correctly–total number of questions–difficulty level

Questions and clues
The following difficulty levels should be supported:
1. No clue is given and only a ‘?’ is shown. Example: What is the capital of France? ?
2. A set of blank dashes seprated by spaces is displayed, one for every letter in the answer. Example:1What is the capital of France?- - - - -
3. The first and the last letters are shown. Example:What is the capital of France?P - - - S
4. Two random letters from the answer are shown in their correct position. Example: What is the capital of France?P - R - -

Advanced marking (over 70%)
1. The questions are asked in random order. 
2. Difficulty level 5: all letters are shown but in random order. Example:What is the capital of France?R S I P A
3. Difficulty level 6. The type of clue is randomly selected from the 5 types listed above.
4. Store the status (correct/incorrect) of all the questions. When the quiz is complete the user is asked ifthey want to view the correct answers to the questions that were wrong.