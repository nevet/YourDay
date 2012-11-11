#include <cassert>

#include "UpdateExecutor.h"

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
			_undoFocusingEntryList = *generalEntryList;

			break;

		case CALENDAR:
			_focusingEntryList = calendarEntryList;
			_undoFocusingEntryList = *calendarEntryList;

			break;

		default:
			break;
	}

	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_resultList = resultList;

	_focusingField = focusingField;
	_encodedUserInput = encodedUserInput;
}

void UpdateExecutor::execute()
{
	int index;
	int newIndex = NO_INDEX_IN_DESCRIPTION;
	string oldEntry, newEntry;
	string tempEntry;
	string newTempEntry;
	string newDate, newTime, newDescription, newPriority, newLocation;
	string oldDate, oldTime, oldDescription, oldPriority, oldLocation;

	bool changeToCalendar = false;

	index=extractIndex(_encodedUserInput);
	
	if(isIndexValid(index))
	{
		oldEntry = _focusingEntryList->at(index-1);		
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

void UpdateExecutor::addNewEntryToRightPosition(string newEntry,int index, int newIndex, bool changeToCalendar)
{
	vector<string>::iterator position;
	int thresholdValue;
	string tempEntry;

	if(changeToCalendar)
	{
		_calendarEntryList->push_back (newEntry);
		position = _focusingEntryList->begin() + index - 1;
		_focusingEntryList->erase(position);	
	}
	else if (newIndex != NO_INDEX_IN_DESCRIPTION)
	{
		if(isIndexValid(newIndex))
		{
			tempEntry = _focusingEntryList -> at(index - 1);
			position = _focusingEntryList->begin() +newIndex -1;

			if( index >= newIndex)
				thresholdValue = 0;
			else 
				thresholdValue = 1;

			_focusingEntryList->insert(position + thresholdValue , tempEntry);
			position = _focusingEntryList->begin() + index - thresholdValue ;
			_focusingEntryList->erase(position);	
		}
		else
		{
			throw string(MESSAGE_INDEX_NOT_VALID);
		}
	}
	else
	{
		_focusingEntryList->at(index -1) = newEntry ;
	}
	return;
}

int UpdateExecutor::extractNewIndex(string newEntry)
{
	string newDescription;
	int newIndex;

	newDescription = extractDescription(newEntry);
	newIndex = extractIndexFromDescription(newDescription);
	
	return newIndex;
}

string UpdateExecutor::constructNewEntry(string oldEntry)
{
	string newEntry = DELIMINATOR + DELIMINATOR;
	string oldAndNewEntries[CHOICES_OF_ENTRY][TOTAL_NO_OF_FIELDS];
	string entries[CHOICES_OF_ENTRY];
	entries[OLD_ENTRY] = oldEntry;
	entries[NEW_ENTRY] = _encodedUserInput;

	for(int i=OLD_ENTRY; i<CHOICES_OF_ENTRY; i++)
	{
		oldAndNewEntries[i][DESCRIPTION_FIELD] = extractDescription(entries[i]);
		oldAndNewEntries[i][LOCATION_FIELD] = extractLocation(entries[i]);
		oldAndNewEntries[i][TIME_FIELD] = extractTime(entries[i]);
		oldAndNewEntries[i][DATE_FIELD] = extractDate(entries[i]);
		oldAndNewEntries[i][PRIORITY_FIELD] = extractPriority(entries[i]);
	}

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
}

bool UpdateExecutor::isIndexValid(int index)
{
	if(index>0 && index <_focusingEntryList->size())
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
	*_focusingEntryList = _undoFocusingEntryList;
}