/*--------------------------------------------------------------------
// file name:	Table.cpp
// authors:     Ben Clark
// date:		08/17/2017
// description: Table represents the archived data of old quizes.
//--------------------------------------------------------------------*/

#include "Table.h"

/*------------------------------------------------------------------
// name:		operator<<
// description:	outputs the Table as a Table with the name as the title
//				and then each of the rows.
//----------------------------------------------------------------*/
ostream & operator<<(ostream & out, const Table t) {
	vector<Round> rows = t.rows;
	if (rows.size() == 0) return out;

	out << "  --------------------------------------" << endl;
	out << "  | " << t.name << "                                |" << endl;
	out << "  |------------------------------------|" << endl;
	out << "  | Quiz | Score | Time(Sec)|   Date   |" << endl;
	out << "  |------|-------|----------|----------|" << endl;

	int i = 0;
	for (; i < rows.size() && i < 9; i++) 
		out << "  | " << (i + 1) << ".   " << rows[i] << endl;
	
	for (; i < rows.size() && i < 99; i++) 
		out << "  | " << (i + 1) << ".  " << rows[i] << endl;
	
	for (; i < rows.size(); i++) 
		out << "  | " << (i + 1) << ". " << rows[i] << endl;
	
	out << "  --------------------------------------" << endl << endl;
	return out;
}