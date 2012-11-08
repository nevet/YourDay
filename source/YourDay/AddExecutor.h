#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class AddExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	int extractDay(string date);
	int extractMonth(string date);
	int extractYear(string date);

	bool isEarlier(string &entry1, string &entry2);
	string _details;
	void quickSort(vector<string> &entryList, int low, int high);
public:
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details) throw (string);

	void execute();
	void undo();
};

#endif