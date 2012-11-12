#ifndef SEARCHEXECUTOR_H
#define SEARCHEXECUTOR_H

#include <vector>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

using namespace std;

#define MAX_ENTRY 50
#define MONTH_NUMBER 12

class SearchExecutor : public Executor
{
private:
	typedef pair<int, int> integerPair;
	
	struct matchInfo
	{
		int continuity;
		int match;
		int change;
		int dis;
		int index;

		int ms;
		int ms_trail;
		int ms_lead;

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

	vector<int> rank;
	vector<int> score;
	vector<string> _combinedEntryList;
	
	int highestRank;
	int totalEntries;
	string _details;

	//memo tables used to record the result of dynamic programming result of
	//editing distance
	int f[MAX_ENTRY][MAX_ENTRY];
	int g[MAX_ENTRY][MAX_ENTRY];

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
	
	const static int MONTH[MONTH_NUMBER];
	
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
	* Most of them are modified functions from language handler to fit the
	* specification of SearchExecutor
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
	void initializeScore();

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
	void initializeRank();

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
	void setRank(int index, int level);

	/*
	* Adjust the Rank Vectors that ensures one of the entry has the highes match
	* with the maximum value (in other words, totalSize)
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* @param currentHighest
	*			is the currently highest rank inside the vector
	* @return void
	*/
	void adjustRank();

	//@author A0091847U
	/**
	* This operation will extract description and location info from the encoded
	* input passed in and then split it words by words and put it into a vetor.
	*
	* @param encodedInput
	*			is the encoded input one wants to split
	* @param list
	*			is the list contains spliting result
	*/
	void splitWords(string encodedInput, vector<string>* list);

	/**
	* This operation is used to calculate match info of match string.
	* 
	* @param i, j
	*			is the posistion info, used for backtrack, entrace will be
	*			(len_pattern, len_match)
	* @param a
	*			is the pattern, i.e. the key
	* @param b
	*			is the match string, i.e. the string under match
	* @param x, y
	*			are strings after editting for a and b correspondingly, for
	*			debuging using
	* @param t
	*			is the structure stored the match info
	*/
	void calInfo(int i, int j, string a, string b, string & x, string & y, matchInfo & t);

	/**
	* This operation is used to tell whether a and b are the same.
	*
	* The operation is called in editing distance dynamic programming.
	*/
	int notsame(char a, char b);

	/**
	* This operation is used to calculate editing distance of two strings and
	* store the match info of match string.
	*
	* @param a
	*			is the key string
	* @param b
	*			is the match string, i.e. the string under match
	*/
	void edit(string a, string b, matchInfo & ans);

	/**
	* This function is used to judge whether the first match info is more
	* relavent than the other match info.
	*
	* @return true is a is more relavent than b
	*/
	static bool cmp(matchInfo a, matchInfo b);

	/**
	* This function is used to pick the more relavent match info from two
	* match infos.
	*/
	matchInfo compare(matchInfo a, matchInfo b);

	/**
	* This operation will encode the suggest words in an encoded string for
	* passing purpose.
	*
	* @param suggestWords
	*			is the encoded string
	* @param updWord
	*			is the word that is to be encoded in the encoded string
	*/
	void updateSuggestWords(string* suggestWords, string updWord);

	/**
	* This function is used to tell whether a match info is unrelavent to a
	* given key.
	*
	* @return true if match info is unrelavent to the key
	*/
	bool unrelavent(matchInfo info, string key);

	/**
	* This operation is used to exam relavence between match infos inside
	* a vector and a given key and eliminate unrelavent entries from the vector.
	*
	* @param rank
	*			is the rank assigned to each entries. It is passed in because
	*			if the entry is unrelavent to the key, the rank will be
	*			assigned as the lowest, i.e. 0
	*/
	void examRelavence(vector<matchInfo>* list, vector<int>* rank, string key);

	/**
	* This operation is used to encode generalized index into an encoded entry.
	*
	* Generalized index is defined as:
	*
	*			If an entry with index X and it's in general list, then its
	*			generalized index will be GX;
	*			If an entry with index X and it's in calendar list, then its
	*			generalized index will be CX;
	*/
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
	void checkEntryDate(int index, string keyword);
	
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
	void searchDate(string keyword);

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
	void checkEntryTime(int index, string keyword);

	/*
	* Searches the list for a matching time input
	* @param keyword
	*			is the time keyword from the user's input
	* @param rank
	*			is the vector that keeps the rank of each entry of each keyword
	* This function will only be called if the input keyword is a time
	* THis search function includes checking whether a user's input is in time range.
	*/
	void searchTime(string keyword);

	/**
	* This operation will search plain-text key from all the entries, then
	* assign ranks to each entries and put the suggesting words inside a vector
	* pass in.
	*/
	void searchText(string key, vector<int>* rank, vector<string>* suggestWords);

public:
	SearchExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* matchedEntryList, string details);

	void execute() throw (string);
	void undo();
};

#endif