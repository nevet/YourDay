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
	struct matchInfo
	{
		int continuity, ms, ms_trail, ms_lead, match, change, dis, index;

		matchInfo()
		{
			continuity = ms = ms_trail = ms_lead = match = change = dis = index = 0;
		}
	};

	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _matchedEntryList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	vector<string> _undoMatchedEntryList;
	
	vector<string> _combinedEntryList;

	bool noMatch;

	int f[500][500];
	int g[500][500];

	string _details;
	
	Log log;

	string splitFirstTerm(string* mString);
	
	const static int MONTH[12];
	
	const static int PERFECT_MATCH;
	const static int MEDIOCORE_MATCH;

	bool isDate(string date);
	bool isTime(string time);
	bool isLeap(int year);
	bool isLogicDate(string date);
	bool isLogicTime(string time);
	bool isInTimeRange(string time);

	int extractDay(string date);
	int extractMonth(string date);
	int extractYear(string date);

	int extractHour(string time);
	int extractMinute(string time);

	void splitStartEndTime(string* start, string* end, string timeRange);
	void splitWords(string encodedInput, vector<string>* list);
	

	void initializeVectors(int totalSize, vector<int>* score, vector<int>* rank);
	void initializeRank(int totalSize, vector<int>* rank);
	void initializeCombinedEntry();
	void setRank(int index, int level, vector<int>* rank, int* currentHighest);
	void adjustRank(vector<int>* rank, int currentHighest);

	void calInfo(int i, int j, string a, string b, string & x, string & y, matchInfo & t);
	int notsame(char a, char b);
	void edit(string a, string b, matchInfo & ans);
	static bool cmp(matchInfo a, matchInfo b);
	matchInfo compare(matchInfo a, matchInfo b);

	void searchDate(string keyword, vector<int>* rank);
	void searchTime(string keyword, vector<int>* rank);
	void searchText(string keyword, vector<int>* rank);

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