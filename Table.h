/*--------------------------------------------------------------------
// file name:	Table.h
// authors:     Ben Clark
// date:		08/17/2017
// description: Table represents the archived data of old quizes.
//--------------------------------------------------------------------*/

#pragma once
#include <string>
#include <vector>

using namespace std;

struct Round {
	/*------------------------------------------------------------------
	// name:		Round
	// description:	takes in a score, time, and date. The score and date
	//				are initilized as is. Time is padded to length 10.
	//----------------------------------------------------------------*/
	Round(int s = 0, int t = 0, string d = "") : score(s), date(d) {
		for (time = " " + to_string(t); time.size() < 10; time += " ");
	}

	/*------------------------------------------------------------------
	// name:		operator<<
	// description:	Outputs Round as a row in the table. Score, then
	//				time, and date are displayed as columns.
	//----------------------------------------------------------------*/
	friend ostream & operator<<(ostream & out, const Round r) {
		(r.score == 10) ? (out << "| ") : (out << "|  ");
		return (out << r.score << "/10 |" << r.time << "|" << r.date << "|");
	}

	int score;
	string time;
	string date;
};

class Table {
public:
	/*------------------------------------------------------------------
	// name:		Table
	// description:	Takes in a string that represents the name of the 
	//				table.
	//----------------------------------------------------------------*/
	Table(string n = "") : name(n) {}

	/*------------------------------------------------------------------
	// name:		addRow
	// description:	Takes in a round to be added to the table.
	//----------------------------------------------------------------*/
	void addRow(Round r) { rows.push_back(r); }

	/*------------------------------------------------------------------
	// name:		operator<<
	// description:	outputs the Table as a Table with the name as the title
	//				and then each of the rows.
	//----------------------------------------------------------------*/
	friend ostream & operator<<(ostream & out, const Table t);

private:
	vector<Round> rows;
	string name;

};