#include <cassert>

#include "UpdateExecutor.h"
//@author A0091734A
UpdateExecutor::UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, vector<string>* resultList,
							   string encodedUserInput, Signal focusingField)
{
	assert(encodedUserInput!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(focusingField!=GENERAL || focusingField!=CALENDAR);

	switch (focusingField)
	{
		case GENERAL:
			_focusingEntryList = generalEntryList;
			break;

		case CALENDAR:
			_focusingEntryList = calendarEntryList;
			break;

		default:
			break;
	}

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_resultList = resultList;

	_focusingField = focusingField;
	_encodedUserInput = encodedUserInput;

	_undoCalendarEntryList = *calendarEntryList;
	_undoGeneralEntryList = *generalEntryList;
}

void UpdateExecutor::execute()
{
	int index, newIndex;
	string oldEntry, newEntry;
	string tempEntry;

	bool changeToCalendar = false;

	index=extractIndex(_encodedUserInput);
	
	if(isIndexValid(index))
	{
		oldEntry = _focusingEntryList->at(index);		
		newEntry = constructNewEntry(oldEntry);
		newIndex = extractNewIndex(newEntry);
		changeToCalendar = verifyTheFiledChange(newEntry);
		
		_resultList->push_back(newEntry);
		addNewEntryToRightPosition(newEntry, index, newIndex, changeToCalendar);
	}
	else
	{
		throw string(MESSAGE_INDEX_NOT_VALID);
	}

}
//Check whether the update makes a general entry become a calendar entry
bool UpdateExecutor::verifyTheFiledChange(string newEntry)
{
	if(extractDate(newEntry)!=NULL_STRING || extractTime(newEntry)!= NULL_STRING)
	{
		if(_focusingField == GENERAL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}
/**
* This function is used to put newEntry into a right entrylist. 
* There are two special situations:
* Situation 1:
* When the general entry are updated, and the date/time filed information is added into oldEntry,
* Then the new entry would be added into calendar list as it is not general entry anymore.
* Situation 2:
* When the user wants to update the index of entry. 
*/
void UpdateExecutor::addNewEntryToRightPosition(string newEntry,int index, int newIndex, bool changeToCalendar)
{
	vector<string>::iterator position;
	int thresholdValue;
	string tempEntry;
	//Situation 1
	if(changeToCalendar)
	{
		_calendarEntryList->push_back (newEntry);
		position = _focusingEntryList->begin() + index ;
		_focusingEntryList->erase(position);	
	}
	//Situation 2
	else if (newIndex != NO_INDEX_IN_DESCRIPTION)
	{
		if(isIndexValid(newIndex))
		{
			tempEntry = _focusingEntryList -> at(index );
			//There are two situation when updating the index to newIndex. 
			if( index >= newIndex)
				thresholdValue = -1;
			else 
				thresholdValue = 0;

			position = _focusingEntryList->begin() +newIndex ;
			_focusingEntryList->insert(position + (1 + thresholdValue) , tempEntry);
			position = _focusingEntryList->begin() +(index -thresholdValue);
			_focusingEntryList->erase(position);	
		}
		else
		{
			throw string(MESSAGE_INDEX_NOT_VALID);
		}
	}
	else
	{
		_focusingEntryList->at(index) = newEntry ;
	}
	return;
}
/**
*This function checks whether the user wants to update index. 
*If the newIndex is valid, then the Index-th entry would be updated to newIndex-th entry
*/
int UpdateExecutor::extractNewIndex(string newEntry)
{
	string newDescription;
	int newIndex;

	newDescription = extractDescription(newEntry);
	newIndex = extractIndexFromDescription(newDescription);
	
	return newIndex;
}
/**
*This function aims to construct a new entry based on the oldEntry
*Only the field updated would be added/edited into the new entry.
*eg1.oldEntry = "##havelunch####*#"  (Assume entry 1)
*   user input: update 1 at soc
*   newEntry = "##havelunc#soc###*#"
*eg2.oldEntry = "##have lunch#####" (Assume entry 1)
*   user input: update 1 have dinner;
*	newEntry = "##have dinner#####";
*/
string UpdateExecutor::constructNewEntry(string oldEntry)
{
	string newEntry = DELIMINATOR + DELIMINATOR;
	string oldAndNewEntries[CHOICES_OF_ENTRY][TOTAL_NO_OF_FIELDS];
	string entries[CHOICES_OF_ENTRY];
	entries[OLD_ENTRY] = oldEntry;
	entries[NEW_ENTRY] = _encodedUserInput;
	//Store old entry and new entry into a 2-d array,first dimension indicates old-entry or new-entry.
	//Second dimension indicates 5 different fields.
	for(int i=OLD_ENTRY; i<CHOICES_OF_ENTRY; i++)
	{
		oldAndNewEntries[i][DESCRIPTION_FIELD] = extractDescription(entries[i]);
		oldAndNewEntries[i][LOCATION_FIELD] = extractLocation(entries[i]);
		oldAndNewEntries[i][TIME_FIELD] = extractTime(entries[i]);
		oldAndNewEntries[i][DATE_FIELD] = extractDate(entries[i]);
		oldAndNewEntries[i][PRIORITY_FIELD] = extractMark(entries[i]);
	}
	//The real process of constructing newEntry, if any field in userInput is empty,
	//the field information would be inherited from oldEntry.
	for(int numOfField=0; numOfField<TOTAL_NO_OF_FIELDS; numOfField++ )
	{
		if(oldAndNewEntries[NEW_ENTRY][numOfField] != NULL_STRING)
		{
			newEntry = newEntry + oldAndNewEntries[NEW_ENTRY][numOfField] + DELIMINATOR;
		}
		else 
		{
			newEntry = newEntry + oldAndNewEntries[OLD_ENTRY][numOfField] + DELIMINATOR;
		}
	}
	return newEntry;
}
//The index is only valid when 0<=index<Total Number of Entry List
bool UpdateExecutor::isIndexValid(int index)
{
	if(index>=0 && index < _focusingEntryList->size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UpdateExecutor::undo()
{
	*_generalEntryList = _undoGeneralEntryList;
	*_calendarEntryList = _undoCalendarEntryList;
}