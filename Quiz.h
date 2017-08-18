/*--------------------------------------------------------------------
// file name:	Quiz.h
// authors:     Ben Clark
// date:		08/17/2017
// description: Quiz represents the quiz given for the trachtenberg test.
//--------------------------------------------------------------------*/

#pragma once
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <windows.h>

using namespace std;

struct Problem {
	/*------------------------------------------------------------------
	// name:		Problem
	// description:	initilizes the multipler and mutiplicand to the 
	//				given values.
	//----------------------------------------------------------------*/
	Problem(int multiplier = 0, int multiplicand = 0) : multiplier(multiplier), multiplicand(multiplicand) {}

	/*------------------------------------------------------------------
	// name:		getAnswer
	// description:	solves the multiplication problem and returns the answer.
	//----------------------------------------------------------------*/
	int getAnswer() { return multiplier * multiplicand; }

	/*------------------------------------------------------------------
	// name:		getProblem
	// description:	returns the problem as a string with a X between the
	//				multiplier and multiplicand.
	//----------------------------------------------------------------*/
	string getProblem() { return to_string(multiplier) + " X " + to_string(multiplicand); }

	int multiplier;
	int multiplicand;
};

class Quiz {
public:
	/*------------------------------------------------------------------
	// name:		Quiz
	// description:	Gets quiz difficulty, then initilizes the problem 
	//				set by generating random numbers.
	//----------------------------------------------------------------*/
	Quiz();

	/*------------------------------------------------------------------
	// name:		giveQuiz
	// description:	Using the problem set outputs the quiz, then records
	//				the answers and tallies the number of questions 
	//				answered correctly.
	//----------------------------------------------------------------*/
	void giveQuiz();

	/*------------------------------------------------------------------
	// name:		getNumCorrect
	// description:	returns the number of questions answered correctly.
	//----------------------------------------------------------------*/
	int getNumCorrect() { return numCorrect; }

	/*------------------------------------------------------------------
	// name:		getDifficulty
	// description:	returns the quizes difficulty.
	//----------------------------------------------------------------*/
	int getDifficulty() { return difficulty; }

	/*------------------------------------------------------------------
	// name:		operator<<
	// description:	outputs the quiz as a table with problem, answer, 
	//				attempt, and ? as columns. ? is marked with an x if
	//				the problem was answerwed incorrectly.
	//----------------------------------------------------------------*/
	friend ostream & operator<<(ostream & out, Quiz q);

private:
	/*------------------------------------------------------------------
	// name:		generateNumber
	// description:	generates a random number with the number of digits
	//				specified.
	//----------------------------------------------------------------*/
	int generateNumber(int digits);

	int difficulty;
	int numCorrect;
	vector<Problem> problems;
	vector<int> answers;
	const int difficultyDigits[4][2] = { { 2, 1 }, { 2, 2 }, { 3, 2 }, { 3, 3 } };
};

/*------------------------------------------------------------------
// name:		addSpaces
// description:	Takes in a string and puts one " " in front, then
//				pads the string with " " until it is of length 10
//----------------------------------------------------------------*/
string addSpaces(string s);

/*------------------------------------------------------------------
// name:		ClearScreen
// description:	Clears the console window.
//----------------------------------------------------------------*/
void ClearScreen();