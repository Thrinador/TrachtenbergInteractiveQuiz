/*--------------------------------------------------------------------
// file name:	Source.cpp
// authors:     Ben Clark
// date:		08/17/2017
// description: The Driver for the program. Pulls data from the file,
//				then gives as many quizes as the user wants, and finally
//				reoutputs to the file.
//--------------------------------------------------------------------*/

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Quiz.h"
#include "Table.h"

using namespace std;

const string FILENAME = "Trachtenberg Quiz results.txt";

/*------------------------------------------------------------------
// name:		endQuizes
// description:	Prompts the user if they want another quiz.
//----------------------------------------------------------------*/
bool endQuizes() {
	ClearScreen();
	cout << endl << "Would you like another quiz(Y/N)? " << endl;
	char answer = 0;
	cin >> answer;
	return (answer == 'n' || answer == 'N');
}

/*------------------------------------------------------------------
// name:		intro
// description:	Prints out a short intro to the program.
//----------------------------------------------------------------*/
void intro() {
	cout << "** Trachtenberg Interactive Quiz **" << endl << endl
	     << "This program gives quizes with scores to help learn" << endl
		 << "the Trachtenberg speed multiplication system." << endl << endl;
}

/*------------------------------------------------------------------
// name:		getDate
// description:	gets the current date and formats it to MM-DD-YYYY
//----------------------------------------------------------------*/
string getDate() {
	time_t rawtime = time(&rawtime);
	struct tm today;
	localtime_s(&today, &rawtime);

	string month = today.tm_mon + 1 < 10 ? "0" + to_string(today.tm_mon + 1) : to_string(today.tm_mon + 1);
	string day = today.tm_mday < 10 ? "0" + to_string(today.tm_mday) : to_string(today.tm_mday);
	string year = to_string(today.tm_year + 1900);

	return month + "-" + day + "-" + year;
}

/*------------------------------------------------------------------
// name:		stringToNum
// description:	attempts to turn a string into a number then returns
//				the result.
//----------------------------------------------------------------*/
int stringToNum(string s) {
	stringstream ss(s);
	int num = 0;
	ss >> num;
	return num;
}

/*------------------------------------------------------------------
// name:		readInFile
// description:	Reads the data from the input file and fill the 4 tables.
//				then returns the tables.
//----------------------------------------------------------------*/
vector<Table> readInFile() {
	vector<Table> trachtenbergQuizes;
	Table oneByOne("2x1");
	Table twoByOne("2x2");
	Table twoByTwo("3x2");
	Table threeByTwo("3x3");

	trachtenbergQuizes.push_back(oneByOne);
	trachtenbergQuizes.push_back(twoByOne);
	trachtenbergQuizes.push_back(twoByTwo);
	trachtenbergQuizes.push_back(threeByTwo);

	fstream fileIn(FILENAME, std::fstream::in);
	string line;

	while (getline(fileIn, line)) {
		//Clears out short and blank lines.
		if (line.size() < 30) continue;

		//Clears out the header for the table and gets the name.
		getline(fileIn, line);
		string name = line.substr(4, 3);
		getline(fileIn, line);
		getline(fileIn, line);
		getline(fileIn, line);
		getline(fileIn, line);
		Table t(name);

		//Rows of the table.
		while (line.find("|") != string::npos) {
			//In a block of text
			int score = stringToNum(line.substr(11, 2));
			int time = stringToNum(line.substr(19, 4));
			string date = line.substr(29, 10);
			Round r(score, time, date);
			t.addRow(r);
			getline(fileIn, line);
		}

		//Sets the table to the appropritate place
		if (name == "2x1") trachtenbergQuizes[0] = t;
		else if (name == "2x2") trachtenbergQuizes[1] = t;
		else if (name == "3x2") trachtenbergQuizes[2] = t;
		else trachtenbergQuizes[3] = t;
	}

	return trachtenbergQuizes;
}

/*------------------------------------------------------------------
// name:		outputFile
// description:	Reads the data in all the tables back to the file.
//----------------------------------------------------------------*/
void outputFile(vector<Table> trachtenbergQuizes) {
	fstream out(FILENAME, std::fstream::out);
	
	out << "Trachtenberg Quiz Results:" << endl;
	out << "--------------------------" << endl;
	out << endl;
	
	for (Table t : trachtenbergQuizes) out << t;
	
	out.close();
}

/*------------------------------------------------------------------
// name:		main
// description: Prints the intro, then pulls data from file. Gives 
//				quizes to the user until they are done, and finally
//				reoutputs the data back to the textfile.
//----------------------------------------------------------------*/
int main() {
	intro();
	vector<Table> trachtenbergQuizes = readInFile();

	while (true) {
		//Gives the quiz and records the time it takes to take the quiz.
		Quiz quiz;
		chrono::steady_clock::time_point start = chrono::steady_clock::now();
		quiz.giveQuiz();
		chrono::steady_clock::time_point end = chrono::steady_clock::now();

		//Build a round from the quiz, then add it to the proper table.
		int score = quiz.getNumCorrect();
		int seconds = chrono::duration_cast<chrono::seconds>(end - start).count();
		
		//Processes the quiz into a round, then adds that to the corresponding table.
		Round r(score, seconds, getDate());
		trachtenbergQuizes[quiz.getDifficulty()].addRow(r);

		//Output results of the quiz to the screen.
		ClearScreen();
		cout << quiz;
		cout << score << "/10 problems correct." << endl;
		cout << "It took " << seconds << " seconds to complete the quiz." << endl << endl;
		cout << "Press enter to continue...";
		cin.get();
		
		//Outputs the tables back to file.
		outputFile(trachtenbergQuizes);

		//Check to see if the user wants to take another quiz.
		if (endQuizes()) break;
	}	
	return 0;
}
