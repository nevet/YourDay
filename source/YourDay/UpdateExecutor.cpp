#include <cassert>

#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField)
{
	assert(details!="");
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
	_focusingField = focusingField;
	_details = details;
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

	vector<string>::iterator position;
	
	newEntry = "##";

	index=extractIndex(_details);
	
	if(index < 1)
	{
		throw string ("index is not existing\n");
	}
	else if(index > (_focusingEntryList->size()))
	{
		throw string ("index is larger than list size\n");
	}
	else 
	{
		oldEntry = _focusingEntryList->at(index-1);
		
		newDescription = extractDescription(_details);
		oldDescription = extractDescription(oldEntry);
		if(newDescription == "")
		{
			newEntry = newEntry + oldDescription + "#";
		}
		else 
		{
			if(extractIndexFromDescription(newDescription) != NO_INDEX_IN_DESCRIPTION)
			{
				newIndex = extractIndexFromDescription(newDescription);
			}
			else
			{
				newEntry = newEntry + newDescription + "#";	
			}
		}
		
		newLocation = extractLocation(_details);
		oldLocation = extractLocation(oldEntry);
		if(newLocation == "")
		{
			newEntry = newEntry + oldLocation + "#";
		}
		else
		{
			newEntry = newEntry + newLocation + "#" ;
		}
		
		newTime = extractTime(_details);
		oldTime = extractTime(oldEntry);
		if(newTime == "")
		{
			newEntry = newEntry + oldTime + "#";
		}
		else
		{
			changeToCalendar = true;
			newEntry = newEntry + newTime + "#";
		}

		newDate = extractDate(_details);
		oldDate = extractDate(oldEntry);
		if(newDate == "")
		{
			newEntry = newEntry + oldDate + "#";
		}
		else
		{
			changeToCalendar = true;
			newEntry = newEntry + newDate + "#";
		}

		newPriority = extractPriority(_details);
		oldPriority = extractPriority(oldEntry);
		if(newPriority == "")
		{
			newEntry = newEntry + oldPriority + "#";
		}
		else
		{
			newEntry = newEntry + newPriority + "#";
		}
		
		if( _focusingField== GENERAL && changeToCalendar)
		{
			
			_calendarEntryList->push_back (newEntry);
			position = _focusingEntryList->begin() + index - 1;
			_focusingEntryList->erase(position);	
		}
		else if (newIndex != NO_INDEX_IN_DESCRIPTION)
		{
			tempEntry = _focusingEntryList -> at(index - 1);
			newTempEntry = _focusingEntryList -> at(newIndex - 1);
			_focusingEntryList->at(index -1) = newTempEntry;
			_focusingEntryList->at(newIndex -1) = tempEntry;
		}
		else
		{
			 _focusingEntryList->at(index -1) = newEntry ;
		}
	}
}

void UpdateExecutor::undo()
{
	*_focusingEntryList = _undoFocusingEntryList;
}