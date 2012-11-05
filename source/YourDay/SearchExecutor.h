#ifndef SEARCHEXECUTOR_H
#define SEARCHEXECUTOR_H

#include <vector>
#include <algorithm>
#include <sstream>
#include "Executor.h"
#include "Log.h"

using namespace std;


class SearchExecutor : public Executor
{
private:
	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _matchedEntryList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	vector<string> _undoMatchedEntryList;

	string _details;
	
	Log log;

	string splitFirstTerm(string* mString);
	
	const static int MONTH[12];

	bool isDate(string date);
	bool isTime(string time);
	bool isLeap(int year);
	bool isLogicDate(string date);
	bool isLogicTime(string time);
	bool isInTimeRange(string time);

	int extractDay(string date);
	int extractMonth(string date);

	int extractHour(string time);
	int extractMinute(string time);

	void splitStartEndTime(string* start, string* end, string timeRange);

	void initializeVectors(int totalSize, vector<int>* score, vector<int>* rank);
	void searchDate(string key, vector<int>* rank);
	void searchTime(string key, vector<int>* rank);
	void searchText(string key, vector<int>* rank);

	/**
	* Format:  #[index of result in the entry list]#[details]#[location]#[time]#[date]#[priority]#
	*/
	void formatSearchResult(int index, string result, string* formattedResult);
public:
	SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details);

	void execute();
	void undo();
};

#endif