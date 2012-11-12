#ifndef SEARCHEXECUTOR_H
#define SEARCHEXECUTOR_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

using namespace std;

class SearchExecutor : public Executor
{
private:
	typedef pair<int, int> integerPair;
	
	struct matchInfo
	{
		int continuity, match, change, dis, index;
		int ms, ms_trail, ms_lead;

		string str;

		matchInfo()
		{
			continuity = ms = ms_trail = ms_lead = match = change = dis = index = 0;
			str = "";
		}

		matchInfo(string s)
		{
			continuity = ms = ms_trail = ms_lead = match = change = dis = index = 0;
			str = s;
		}
	};

	vector<string>* _calendarEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _matchedEntryList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	vector<string> _undoMatchedEntryList;
	
	vector<string> _combinedEntryList;
	
	string _details;

	int f[50][50];
	int g[50][50];

	bool noMatch;
	int treshold;

	//@author A0088455R
	/**
	* Splits user input's string and retreives the first word
	*
	* @param manipulatedString
	*			is the user's input which going to be manipulated
	*			after the method is called, the first word will be deleted
	* @return first term
	*			is the first word of the user's input
	*
	* e.g.
	* if user's input is "CS2103 meeting at UTown"
	* after the operation, the return will be CS2103 and the manipulated string
	* will be "meeting at UTown"
	*/
	string splitFirstTerm(string* rawString);
	
	const static int MONTH[12];
	
	/**
	* These are the initiation for the values for how good is the match
	* between the keywords and the entries inside the entry list
	* Applicable only for searchDate and searchTime
	*/
	const static int PERFECT_MATCH;
	const static int HIGH_MATCH;
	const static int MEDIOCORE_MATCH;
	const static int LOW_MATCH;
	const static int NO_MATCH;

	/**
	* The following methods assesses whether the data passed are correct
	* Most of them are modified functions from language handler
	*/

	/*
	* Checks whether the input is a date input.
	* @param date
	*			is the tested string
	* @return isDate
	*			whether it's true that the input is a date
	* The format must be DD/MM/YYYY
	* e.g. input = "21/10/2012"
	*	return = true
	*/
	bool isDate(string date);

	/*
	* Checks whether the input is a time input.
	* @param time
	*			is the tested string
	* @return isTime
	*			whether it's true that the input is a time input
	* Format must be HH:MM
	* e.g. input = "21:39"
	*	return = true
	*/
	bool isTime(string time);

	/*
	* Checks whether the input year is a leap year.
	* @param year
	*			is the tested year
	* @return isLeap
	*			whether it's true that the input is a leapYear
	* Format must be HH:MM
	* e.g. input = "2008"
	*	return = true
	*/
	bool isLeap(int year);

	/*
	* Checks whether the input is a logical date input.
	* @param date
	*			is the tested string
	* @return isLogicDate
	*			whether it's a valid date input
	* Format must be DD/MM/YYYY
	* e.g. input = "32/10/2012"
	*	return = false
	*/
	bool isLogicDate(string date);

	/*
	* Checks whether the input is a logical time input.
	* @param time
	*			is the tested string
	* @return isLogicTime
	*			whether it's true that the input is a logical time input
	* Format must be HH:MM
	* e.g. input = "25:39"
	*	return = false
	*/
	bool isLogicTime(string time);

	/*
	* Initializes the Score and Rank Vectors to 0
	* @param totalSize
	*			is the total size of calendar entry list and general entry list
	* @param score
	*			is the vector that keeps the score of each entry
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	*/
	void initializeVectors(int totalSize, vector<int>* score, vector<int>* rank);

	/*
	* Initializes the Rank Vectors to the same value of total size.
	* These values will be decrease every time there is a mismatch during
	* search operation
	* @param totalSize
	*			is the total size of calendar entry list and general entry list
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @return void
	* e.g. there are 100 entries in total
	*			each entry should have initial rank value of 100
	*/
	void initializeRank(int totalSize, vector<int>* rank);

	/*
	* Initializes the _combinedEntryList vector which contains both general entry and
	* calendar entry
	* @param void
	* @return void
	* After this operation the _combinedEntryList vector will contain general entry
	* and the calendar entry
	*/
	void initializeCombinedEntry();
	/*
	* Set's the rank of the entry with the same index as index parameter
	* @param index
	*			is the index of the entry
	* @param level
	*			is the level of match of keyword and entry
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param currentHighest
	*			contains the current highest rank
	* @return void
	*/
	void setRank(int index, int level, vector<int>* rank, int* currentHighest);
	/*
	* Adjust the Rank Vectors that ensures one of the entry has the highes match
	* with the maximum value (in other words, totalSize)
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param currentHighest
	*			is the currently highest rank inside the vector
	* @return void
	*/
	void adjustRank(vector<int>* rank, int currentHighest);

	void splitWords(string encodedInput, vector<string>* list);
	void calInfo(int i, int j, string a, string b, string & x, string & y, matchInfo & t);
	int notsame(char a, char b);
	void edit(string a, string b, matchInfo & ans);
	static bool cmp(matchInfo a, matchInfo b);
	matchInfo compare(matchInfo a, matchInfo b);
	void updateSuggestWords(string* suggestWords, string updWord);
	bool unrelavent(matchInfo info, string key);
	void examRelavence(vector<matchInfo>* list, string key);

	void encodeIndex(string* encodedEntry, int index);

	//@author A0088455R
	/**
	* Checks an Entry at index "index" for its matching level with the keyword and
	* sets the rank
	* @param index
	*			is the index of the entry inside the list
	* @param keyword
	*			is the date keyword from the user's input
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param highest rank
	*			is the currently highest rank inside the vector
	* @return void
	*
	* The rank will set according to its predefined matching level
	**/
	void checkEntryDate(int index, vector<int>* rank, string keyword, int &highestRank);
	
	/*
	* Searches the list for a matching date input
	* @param keyword
	*			is the date keyword from the user's input
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param currentHighest
	*			is the currently highest rank inside the vector
	* This function will only be called if the input keyword is a date
	*/
	void searchDate(string keyword, vector<int>* rank);

	/**
	* Checks an Entry at index "index" for its matching level with the time keyword and
	* sets the rank accordingly
	* this method includes the searches between time ranges
	* @param index
	*			is the index of the entry inside the list
	* @param keyword
	*			is the date keyword from the user's input
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param highest rank
	*			is the currently highest rank inside the vector
	* @return void
	*
	* The rank will set according to its predefined matching level
	**/
	void checkEntryTime(int index, vector<int>* rank, string keyword , int &highestRank);

	/*
	* Searches the list for a matching time input
	* @param keyword
	*			is the time keyword from the user's input
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* This function will only be called if the input keyword is a time
	* THis search function includes checking whether a user's input is in time range.
	*/
	void searchTime(string keyword, vector<int>* rank);

	void searchText(string key, vector<int>* rank, vector<string>* suggestWords);

	/**
	* Format:  #[index of result in the entry list]#[details]#[location]#[time]#[date]#[priority]#
	*/
	void formatSearchResult(int index, string result, string* formattedResult);
public:
	SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details);

	void execute() throw (string);
	void undo();
};

#endif