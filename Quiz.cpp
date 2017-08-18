/*--------------------------------------------------------------------
// file name:	Quiz.cpp
// authors:     Ben Clark
// date:		08/17/2017
// description: Quiz represents the quiz given for the trachtenberg test.
//--------------------------------------------------------------------*/

#include "Quiz.h"

using namespace std;

/*------------------------------------------------------------------
// name:		Quiz
// description:	Gets quiz difficulty, then initilizes the problem
//				set by generating random numbers.
//----------------------------------------------------------------*/
Quiz::Quiz() {
	difficulty = 4;
	while (difficulty < 0 || difficulty > 3) {
		cout << "Enter the quiz difficulty(0 - 3) where 0 is easiest: ";
		cin >> difficulty;
	}

	for (int i = 0; i < 10; i++) {
		Problem p(generateNumber(difficultyDigits[difficulty][0]), 
				  generateNumber(difficultyDigits[difficulty][1]));

		problems.push_back(p);
	}
}

/*------------------------------------------------------------------
// name:		giveQuiz
// description:	Using the problem set outputs the quiz, then records
//				the answers and tallies the number of questions
//				answered correctly.
//----------------------------------------------------------------*/
void Quiz::giveQuiz() {
	for (int i = 0; i < problems.size(); i++) {
		ClearScreen();
		cout << problems[i].getProblem() << " = ";
		int answer = 0;
		cin >> answer;
		if (answer == problems[i].getAnswer()) numCorrect++;
		answers.push_back(answer);
	}
}

/*------------------------------------------------------------------
// name:		generateNumber
// description:	generates a random number with the number of digits
//				specified.
//----------------------------------------------------------------*/
int Quiz::generateNumber(int digits) {
	if (digits < 1) return 0;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> dist(pow(10, digits - 1), pow(10, digits) - 1);
	return dist(rng);
}

/*------------------------------------------------------------------
// name:		operator<<
// description:	outputs the quiz as a table with problem, answer,
//				attempt, and ? as columns. ? is marked with an x if
//				the problem was answerwed incorrectly.
//----------------------------------------------------------------*/
ostream & operator<<(ostream & out, Quiz q) {
	vector<Problem> problems = q.problems;
	vector<int> answers = q.answers;

	out << "--------------------------------------" << endl;
	out << "| Problem  | Attempt  | Answer   | ? |" << endl;
	out << "|----------|----------|----------|---|" << endl;

	for (int i = 0; i < problems.size(); i++) 
		out << "|" << addSpaces(problems[i].getProblem())
			<< "|" << addSpaces(to_string(answers[i]))
			<< "|" << addSpaces(to_string(problems[i].getAnswer()))
			<< "| " << (answers[i] == problems[i].getAnswer() ? ' ' : 'X') << " |" << endl;
	
	out << "--------------------------------------" << endl;

	return out;
}

/*------------------------------------------------------------------
// name:		addSpaces
// description:	Takes in a string and puts one " " in front, then
//				pads the string with " " until it is of length 10
//----------------------------------------------------------------*/
string addSpaces(string s) {
	for (s = " " + s; s.size() < 10; s += " ");
	return s;
}

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console window.
//----------------------------------------------------------------*/
void ClearScreen() {
	std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	// Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	//Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	//Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}