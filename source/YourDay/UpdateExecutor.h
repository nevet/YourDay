#ifndef UPDATEEXECUTOR_H
#define UPDATEEXECUTOR_H

#include <vector>
#include "Executor.h"
#include <string>


//@author A0091734A
const static string NULL_STRING = "";
const static string DELIMINATOR = "#";
static const string MESSAGE_INDEX_NOT_VALID = "Sorry, There is no such entry with this index :) \n";
static const int TOTAL_NO_OF_FIELDS = 5;
static const int CHOICES_OF_ENTRY = 2;

enum {OLD_ENTRY, NEW_ENTRY};
enum {DESCRIPTION_FIELD, LOCATION_FIELD, TIME_FIELD, DATE_FIELD, PRIORITY_FIELD};
using namespace std;
/**
* UpdateExecutor is used to update the information of existing entry.
* The UpdateExecutor is able to modify the time/date/description/index/location/priority of any entry,
* according to the user input.
* It derives from Executor supper class, so it contains execute() and undo()method.
* The execute will update according to the current storage and the user input.
* The encoded user input is saved in a string called "details"
*/
class UpdateExecutor : public Executor
{
private:
	vector<string>* _focusingEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _calendarEntryList;
	vector<string>* _resultList;

	vector<string> _undoGeneralEntryList;
	vector<string> _undoCalendarEntryList;
	//signal indicates which area the user choose
	Signal _focusingField;
	string _encodedUserInput;

	/**
	* @param index
	* @return true if the index valid
			  false if invalid
	*/
	bool isIndexValid(int index);

	/**
	* @param newEntry
	* @return true if a general Entry was updated to a Calendar Entry
			  false if not
	*/
	bool verifyTheFiledChange(string newEntry);
	
	/**
	* @param newEntry
	* @return newIndex if user wants to update the index.
		      if not , -1 would be returned.
	*/
	int extractNewIndex(string newEntry);
	/**
	* @param newEntry
	* @param index
	* @param newIndex
	* @param changToCalendar
	*
	* @return newIndex if user wants to update the index.
		      if not , -1 would be returned.
	*/
	void addNewEntryToRightPosition(string newEntry,int index, int newIndex, bool changeToCalendar);
	string constructNewEntry(string oldEntry);

public:
	UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList, 
				   string encodedUserInput, Signal focusingField);

	void execute();
	void undo();
};

#endif