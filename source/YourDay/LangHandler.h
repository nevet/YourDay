/**
    YourDay
    LangHandler.h
    Purpose: Calculates the total of 6 checks

    @author A0091847U
*/
#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <map>
#include <ctime>
#include <cassert>

#include "Signal.h"

#include "StorageHandler.h"

#include "Executor.h"
#include "AddExecutor.h"
#include "DeleteExecutor.h"
#include "SearchExecutor.h"
#include "UpdateExecutor.h"
#include "ExitExecutor.h"

#include "Log.h"


using namespace std;

class LangHandler
{
private:	
	Log log;

	Signal command;

	string details;

	const static int MONTH[12];

	const static char SPACE_BAR;
	const static char DELIMINATOR;
	const static char PRIORITY_INDICATOR;

	const static bool DELETE_MULTIPLE_INDEX_ENABLE;
	const static bool UPDATE_MULTIPLE_INDEX_ENABLE;
	const static bool ADD_DATE_AUTOFILL_ENABLE;
	const static bool UPDATE_DATE_AUTOFILL_ENABLE;
	const static bool ADD_EMPTY_DESCRIPTION_ENABLE;
	const static bool UPDATE_EMPTY_DESCRIPTION_ENABLE;
	const static bool SEARCH_EMPTY_DESCRIPTION_ENABLE;
	
	const static string ADD_MARK_INDICATOR;
	const static string LOCATION_INDICATOR;
	const static string NULL_STRING;
	const static string UPDATE_MARK_INDICATOR;
	const static string UPDATE_UNMARK_INDICATOR;

	/**
	* These functions will verify whether thar param passed in is in a valid
	* form or logical. Details of the functions will be listed below.
	*/

	/**
	* This function is used to check whether the year passed in is a leap year.
	*
	* @return true if the year is a leap year.
	*/
	bool isLeap(int year);

	/**
	* This function is used to check whether a string is an integer.
	*
	* @return true if the string is an integer.
	*/
	bool isInt(string inx);
	
	/**
	* This function is used to check whether a string is in a valid data
	* form.
	* 
	* Date form is defined as: DD/MM/YYYY
	*
	* In the foramt, DD is the day, MM is the month, and YYYY is the year.
	*
	* Note that the function will accept leading zeros.
	*
	* @return true if the date is in a valid date form.
	*/
	bool isLogicDate(string date);

	/**
	* This function is used to check whether a string is in a valid time
	* form.
	* 
	* Time form is defined as: HH:MM-HH:MM
	*
	* In the foramt, hh is the hour, MM is the minute.
	*
	* Note that the function will accept leading zeros.
	*
	* @return true if the date is in a valid time form.
	*/
	bool isLogicTime(string time);

	/**
	* These functions will return the suffix/prefix of a string from/to the
	* position specified by pos.
	*
	* @param str
	*			is the string one wants to get suffix/prefix.
	* @param pos
	*			is the starting/ending posistion of the suffix/prefix.
	*
	* @return corresponding suffix/prefix the the string.
	*/
	string getSuffix(string str, int pos);
	string getPrefix(string str, int pos);

	/**
	* These operations will split up user input and put into correct field.
	*/

	/**
	* This operation will split up priority info, if possible, given by the
	* user input and put it into priority field of the encoded entry.
	*
	* @param str
	*			is the user input.
	* @param priority
	*			is the priority field of encoded entry.
	* @param indicator
	*			is the priority indicator
	* @param token
	*			is the token that will be put into prioity field
	*/
	void splitPriority(string* str, string* priority, string indicator, char token) throw (string);
	
	/**
	* This operation will split up location info, if possible, given by the
	* user input and put it into location field of the encoded entry.
	*
	* @param str
	*			is the user input.
	* @param location
	*			is the location field of encoded entry.
	*/
	void splitLocation(string* str, string* location) throw (string);

	/**
	* This operation will split up index info, if possible, given by the
	* user input and put it into index field of the encoded entry.
	*
	* @param str
	*			is the user input.
	* @param index
	*			is the index field of encoded entry.
	* @param multiple
	*			is the indicator of multiple index enable, true if multiple
	*			index is enabled
	*/
	void splitIndex(string* str, string* index, bool multiple) throw (string);
	
	/**
	* This operation will split up date info, if possible, given by the
	* user input and put it into date field of the encoded entry.
	*
	* @param str
	*			is the user input.
	* @param date
	*			is the date field of encoded entry.
	*/
	void splitDate(string* str, string* date) throw (string);

	/**
	* This operation will split up time info, if possible, given by the
	* user input and put it into time field of the encoded entry.
	*
	* @param str
	*			is the user input.
	* @param time
	*			is the time field of encoded entry.
	* @param autoFill
	*			is the indicator of auto fill date enable, true if date should
	*			be auto filled up
	*/
	void splitTime(string* str, string* time, string* date, bool autoFill) throw (string);

	/**
	* This operation will split up description info, if possible, given by the
	* user input and put it into description field of the encoded entry.
	*
	* Note, this operation should be called after all other fields have been
	* splited.
	*
	* @param str
	*			is the user input.
	* @param description
	*			is the description field of encoded entry.
	* @param empty
	*			is the indicator of empty description enable, true if empty
	*			descritpin is allowed
	*/
	void splitDescription(string* str, string* description, bool empty) throw (string);

	/**
	* This operation will fill up the date field of the encoded entry with
	* current date.
	*/
	void fillUpDate(string* date);

	/**
	* These operations will regulate corresponding fields in the encoded entry.
	*/

	/**
	* This operation will regulate the date to date form.
	* 
	* Date form is defined as: DD/MM/YYYY
	*
	* In the foramt, DD is the day, MM is the month, and YYYY is the year.
	*/
	void regulateDate(string* date);

	/**
	* This operation will regulate the time to time form.
	* 
	* Time form is defined as: HH:MM-HH:MM
	*
	* In the foramt, hh is the hour, MM is the minute.
	*/
	void regulateTime(string* time);

	/**
	* This operation will regulate the location info so that the info will not
	* contain leading or trailing spaces.
	*/
	void regulateLocation(string* location);

	/**
	* This operation will regulate the description info so that the info will
	* not contain leading or trailing spaces.
	*/
	void regulateDescription(string* description);

	/**
	* This operation is used to eliminate leading and trailing spaces of a
	* string.
	* 
	* @param str
	*			is the string needs to be spaces-freed
	*/
	void eliminateSpaces(string* str);

	/**
	* Encodes the raw string into the correct saving format
	*
	* @param input
	*			is a raw string that needs to be encoded
	* @param command
	*			is the command type
	* @return encoded string, format of the string is:
	* 
	* #index#description#location#time#date#priority#
	*
	* index:
	*		this field contains index information required by delete and update
	*		functions.
	* description:
	*		this field contains description of the task required by add, search
	*		and update functions.
	* location:
	*		this field contains location information required by add and search
	*		functions.
	* time:
	*		this field contains time information required by add and search
	*		functions.
	* date:
	*		this field contains date information required by add and search
	*		functions.
	* priority:
	*		this field contains priority information required by add and search
	*		functions.
	*		
	* Note that some fields are not necessarily required. However, if one field
	* if not required for a certain function, that field should not be OMITTED.
	*
	* e.g
	*
	* userInput = "add CS2103 TUT at COM on Friday"
	* encoded	= "##CS2103 TUT#COM##Friday##"
	*
	* explaination:
	*
	* since index field, time field and priority field are missing,
	* corresponding fields should be left as "blank".
	*
	* userInput = "delete 1"
	* encoded	= "#1######"
	*
	* explaination:
	*
	* only index field is specified, so other fields should be "blank".
	*/
	void encoder(string input, Signal command) throw (string);

	//@author A0088455R
	/**
	* This operation will set command type using userCommand. If userCommand
	* took from the user is invalid, COMMAND_E Signal will be set.
	*/
	void setCommand(string userCommand);

public :
	
	LangHandler();

	//@author A0088455R
	/**
	* Seperates user input's string into 2 parts, the command and the
	* encoded string.
	*
	* User command will be stored in private string userCommand;
	* Details info will be stored in private string details
	* 
	* e.g
	*
	* userInput = "add CS2103 tutorial at COM1";
	* return = {userCommand = "add", detials = "#CS2103 tutorial#COM1##"}
	* 
	* userInput = "delete 1";
	* return = {userCommand = "delete", details = "#1###"}
	*
	* details about format of encoded string can be found in encoded().
	*/
	void separate(string userInput) throw (string);

	/**
	* This operation will pack up an specific executor w.r.t user's command
	*/
	Executor* pack(bool* quit, Signal focusingField,
							   vector<string>* generalEntryList, 
							   vector<string>* calendarEntryList,
							   vector<string>* resultList,
							   StorageHandler* store);

	~LangHandler();
};


#endif