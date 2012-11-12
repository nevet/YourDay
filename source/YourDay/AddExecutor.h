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
	vector<string>* _resultList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	
	string _details;

	//@author A0088455R	
	/**
	* Manipulates the entry format from the input string to
	* YYYY/MM/DDHH:MM for the isEarlier function
	*
	* @param entry
	*			is the destination list where the user's input is going to be added
	* @return manipulated date and time string
	*			is the extracted and manipulated time and date string
	* NOTE: This function is specifically for the calendar entries
	* e.g
	* if entry = "##CS2103 meeting#UTown#13:00-14:00#21/10/2012##"
	* the return should be 2012/10/2113:00-14:00
	*/
	string manipulateEntryDate(string entry);

	/**
	* Checks whether an encoded entry is earlier than the other compared
	* entry
	*
	* @param entry1
	*			is the destination list where the user's input is going to be added
	* @param entry2
	*			is the encoded user's input
	*			format: "#index#description#location#time#date#priority#"
	* @return isEarlier
	*			is a boolean value whether an entry is earlier than the other
	* NOTE: This function is specifically for the calendar entries
	* e.g
	* if entry1 = "##CS2103 meeting#UTown#13:00-14:00#21/10/2012##"
	* entry2 = "##CS2103 meeting#UTown#13:01-14:00#21/10/2012##"
	* the return should be true
	*/
	bool isEarlier(string &entry1, string &entry2);

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
	**/
	int binarySearch(vector<string>* _entryList, string key, int imin, int imax);

	/**
	* Shifts the vector by 1, starting from the index
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
	**/
	void shiftList(vector<string>* _entryList,int index);

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
	**/
	void addToPosition(vector<string>* _entryList, int position, string input);


public:
	AddExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList, string details);

	void execute() throw (string);
	void undo();
};

#endif