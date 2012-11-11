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
	vector<string>* _resultList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;

	bool isEarlier(string &entry1, string &entry2);
	string _details;

	//@author A0088455R	
	/**
	* Searches the correct index to add the current user's input
	*
	* @param _entryList
	*			is the destination list where the user's input is going to be added
	* @param input
	*			is the encoded user's input
	*			format: "#index#description#location#time#date#priority#"
	* @return index
	*			is the correct index where the entry should be insterted
	* NOTE: This function is specifically for the calendar entries
	* e.g
	* if input = "##CS2103 meeting#UTown#13:00-14:00#21/10/2012##"
	* the return should be the correct index where the entry should be added
	*/
	int searchIndex(vector<string>* _entryList, string input);

	/**
	* Implementation of the binary search itself for searchIndex
	*
	* @param _entryList
	*			is the destination list where the user's input is going to be added
	* @param input
	*			is the encoded user's input
	*			format: "#index#description#location#time#date#priority#"
	* @param imin
	*			is the starting index where the search first commenced
	* @param imax
	*			is the ending index where the search is commenced
	* @return index
	*			is the correct index where the entry should be insterted
	* NOTE: This function is specifically for the calendar entries
	* e.g
	* if input = "##CS2103 meeting#UTown#13:00-14:00#21/10/2012##"
	* the return should be the correct index where the entry should be added
	*/
	int binarySearch(vector<string>* _entryList, string key, int imin, int imax);

	/**
	* This method adds the user's encoded string to the correct position
	*
	* @param _entryList
	*			is the destination list where the user's input is going to be added
	* @param position
	*			is the position where the user's input is going to be added
	* @param input
	*			is the encoded user's input
	*			format: "#index#description#location#time#date#priority#"
	* @return void
	*			
	* NOTE: This function is specifically for the calendar entries
	* e.g
	* if input = "##CS2103 meeting#UTown#13:00-14:00#21/10/2012##"
	* the input will be the added at the index position inside the _entryList
	*/
	void addToPosition(vector<string>* _entryList, int position, string input);


public:
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList, string details);

	void execute() throw (string);
	void undo();
};

#endif