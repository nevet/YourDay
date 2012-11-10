#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;
//@author A0091734A
class AddExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	static int extractDay(string date);
	static int extractMonth(string date);
	static int extractYear(string date);

	static bool isEarlier(string &entry1, string &entry2);
	string _details;
	int partition(vector<string> &entryList, int low, int high);
	void quickSort(vector<string> &entryList, int low, int high);
public:
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details) throw (string);

	void execute();
	void undo();
};

#endif