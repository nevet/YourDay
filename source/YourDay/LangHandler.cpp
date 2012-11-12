/**
    YourDay
    LangHandler.cpp
    Purpose: Encodes user's input and decodes stored entry

    @author A0091847U
*/
#include "LangHandler.h"

const int LangHandler::MONTH[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char LangHandler::SPACE_BAR = ' ';
const char LangHandler::DELIMINATOR = '#';
const char LangHandler::PRIORITY_INDICATOR = '*';

const string LangHandler::ADD_MARK_INDICATOR = " !!!";
const string LangHandler::UPDATE_MARK_INDICATOR = " marked";
const string LangHandler::UPDATE_UNMARK_INDICATOR = " unmarked";
const string LangHandler::LOCATION_INDICATOR = " at ";
const string LangHandler::NULL_STRING = "";

bool LangHandler::isLeap(int year)
{
	bool flag = false;
	
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			flag = true;
		}
	} else
	{
		if (year % 4 == 0)
		{
			flag = true;
		}
	}

	return flag;
}

bool LangHandler::isDate(string date)
{
	int day, month, year;
	
	bool flag = (sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) == 3);

	return flag;
}

bool LangHandler::isTime(string time)
{
	int h1, h2, m1, m2;

	bool flag = (sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2) == 4);

	return flag;
}

bool LangHandler::isInt(string inx)
{
	int x;

	return sscanf(inx.c_str(), "%d", &x) == 1;
}

bool LangHandler::isLogicDate(string date)
{
	int year, month, day;

	bool flag = true;

	//extract year, month and day from the string
	sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
	if (year > 9999 || year < 1000)
	{
		flag = false;
	} else
	if (month > 12 || month < 1)
	{
		flag = false;
	} else
	if (day < 1)
	{
		flag = false;
	} else
	{
		if (day > MONTH[month - 1])
		{
			flag = false;
		} else
		{
			if (!isLeap(year) && month == 2 && day == 29)
			{
				flag =false;
			}
		}
	}

	return flag;
}

bool LangHandler::isLogicTime(string time)
{
	int h1, h2, m1, m2;

	bool flag = true;

	sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2);

	if (h1 > 23 || h1 < 0 || h2 > 23 || h2 < 0)
	{
		flag = false;
	} else
	if (m1 > 59 || m1 < 0 || m2 > 59 || m2 < 0)
	{
		flag = false;
	} else
	{
		if (h1 > h2)
		{
			flag = false;
		} else
		if (h1 == h2 && m1 > m2)
		{
			flag = false;
		}
	}

	return flag;
}

void LangHandler::eliminateSpaces(string* s)
{
	string str = *s;
	
	int len = str.length();
	
	int lead = 0;
	int trail = len - 1;

	if (!str.empty())
	{
		while (lead <= trail && str[lead] == SPACE_BAR)
		{
			lead++;
		}

		while (trail >= lead && str[trail] == SPACE_BAR)
		{
			trail--;
		}

		if (lead <= trail)
		{
			str = str.substr(lead, trail - lead + 1);
		} else
		{
			str = NULL_STRING;
		}
	}

	*s = str;
}

string LangHandler::getPrefix(string str, int pos)
{
	string prefix;

	if (pos == string::npos)
	{
		prefix = str;
	} else
	{
		prefix = str.substr(0, pos);
	}

	eliminateSpaces(&prefix);
	
	return prefix;
}

string LangHandler::getSuffix(string str, int pos)
{
	string suffix;
	
	if (pos == string::npos)
	{
		suffix = NULL_STRING;
	} else
	{
		suffix = str.substr(pos);
	}

	eliminateSpaces(&suffix);
	
	return suffix;
}

void LangHandler::fillUpDate(string* date)
{
	time_t seconds = time(NULL);
	struct tm * timeInfo = localtime(&seconds);

	int year = timeInfo->tm_year + 1900;
	int month = timeInfo->tm_mon + 1;
	int day = timeInfo->tm_mday;

	char tempDate[15];

	*date = NULL_STRING;

	sprintf(tempDate, "%02d/%02d/%d", day, month, year);

	*date += tempDate;
}

void LangHandler::splitPriority(string* str, string* priority, string indicator, char token) throw (string)
{
	string input = *str;
	string token_s;

	if (token == SPACE_BAR)
	{
		token_s = NULL_STRING;
	} else
	{
		token_s = token;
	}
	
	//add a space in front to avoid indicator missing
	input = SPACE_BAR + input;
	//check whether we have priority
	int pos = input.rfind(indicator);
				
	//contains priority info, then we need to judge whether it has been set;
	//if we cannot find the indicator, we leave priority field unchange
	if (pos != string::npos)
	{
		*priority = token_s;
	}
	
	//get rid of priority info
	input = getPrefix(input, pos);

	*str = input;
}

void LangHandler::splitLocation(string* str, string* location) throw (string)
{
	string input = *str;
	
	//add a space before the string in case "at " happens
	input = SPACE_BAR + input;
	//check whether we have location
	int pos = input.rfind(LOCATION_INDICATOR);

	//contains location info; if we cannot find indicator, we leave location
	//unchange
	if (pos != string::npos)
	{
		*location = getSuffix(input, pos + LOCATION_INDICATOR.length());
	}
	
	//get rid of location info
	input = getPrefix(input, pos);

	*str = input;
}

void LangHandler::splitIndex(string* str, string* index, bool multiple) throw (string)
{
	string input = *str;
	string potentialIndex;

	//extract the first term of the input and exam whether it is an integer
	int pos = input.find(SPACE_BAR);
	
	if (multiple)
	{
		//in this mode, we are handling update command, therefore there may be
		//multiple filed and we only need to take in the first field
		potentialIndex = getPrefix(input, pos);

		if (isInt(potentialIndex))
		{
			*index = potentialIndex;
			
			//get rid of index info
			input = getSuffix(input, pos);
		} else
		{
			*index = NULL_STRING;
						
			log.writeException("The first field should be an Integer!");
			throw string ("The first field should be an Integer!\n");
		}
	} else
	{
		//in this mode, we are handling delete command, therefore if multiple
		//entries detected, an exception should be thown since we do not
		//support multiple delete entries
		if (pos == string::npos)
		{
			potentialIndex = getPrefix(input, input.length());
					
			if (isInt(potentialIndex))
			{
				*index = potentialIndex;
			} else
			{
				*index = NULL_STRING;
						
				log.writeException("The first field should be an Integer!");
				throw string ("The first field should be an Integer!\n");
			}
		}
		else
		{
			log.writeException("No Multiple Entry is Allowed!");
			throw string("No Multiple Entry is Allowed!\n");
		}
	}

	*str = input;
}

void LangHandler::splitDate(string* str, string* date) throw (string)
{
	string input = *str;
	string potentialDate;

	//extract the first term of the input and exam whether it is a date
	int pos = input.find(SPACE_BAR);

	if (pos != string::npos)
	{
		potentialDate = getPrefix(input, pos);
	} else
	{
		potentialDate = input;
	}

	//if the potential is a logic date, we take down the date and get rid of it
	//from the input string; else if it is a date but not logical, we throw an
	//exception; else if it is not even a date, date field should be left
	//unchange since nowhere else can find a date, and the input should remain
	//unchange as well.
	if (isDate(potentialDate))
	{
		if (isLogicDate(potentialDate))
		{
			*date = potentialDate;
			input = getSuffix(input, pos);
		} else
		{
			*date = NULL_STRING;
			
			log.writeException("date error");
			throw string ("date error\n");
		}
	}

	*str = input;
}

void LangHandler::splitTime(string* str, string* time, string* date, bool autoFill) throw (string)
{
	string input = *str;
	string potentialTime;

	//extract the first term of the input and exam whether it is a time
	int pos = input.find(SPACE_BAR);

	if (pos != string::npos)
	{
		potentialTime = getPrefix(input, pos);
	} else
	{
		potentialTime = input;
	}

	//if the potential is a logic time, we take down the time and get rid of it
	//from the input string; else if it is a time but not logical, we throw an
	//exception; else if it is not even a time, date field should be left
	//unchange since nowhere else can find a time, and the input should remain
	//unchange.
	if (isTime(potentialTime))
	{
		if (isLogicTime(potentialTime))
		{
			*time = potentialTime;
			input = getSuffix(input, pos);
		} else
		{
			*time = NULL_STRING;
			
			log.writeException("time error");
			throw string ("time error\n");
		}
	}

	//if auto_fill_date is allowed and if date field is omitted with time
	//field specified, we will auto-fill the date field with current date
	if (autoFill)
	{
		if (!time->empty() && date->empty())
		{
			fillUpDate(date);
			log.writeData("date after auto fill up", date);
		}
	}

	*str = input;
}

void LangHandler::splitDescription(string* str, string* description, bool empty) throw (string)
{
	*description = *str;
	
	//only when we are not handling empty_allow description, empty description
	//exception should be thown
	if (*description == NULL_STRING  && !empty)
	{
		log.writeException("Empty Description!");
		throw string ("Empty Description!\n");
	}
}

void LangHandler::regulateDate(string* date)
{
	int year, month, day;
	
	char tempDate[15];

	if (!date->empty())
	{
		sscanf(date->c_str(), "%d/%d/%d", &day, &month, &year);
		sprintf(tempDate, "%02d/%02d/%d", day, month, year);

		*date = NULL_STRING;
		*date += tempDate;
	}
}

void LangHandler::regulateTime(string* time)
{
	int h1, h2, m1, m2;

	char tempTime[15];

	if (!time->empty())
	{
		sscanf(time->c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		sprintf(tempTime, "%02d:%02d-%02d:%02d", h1, m1, h2, m2);

		*time = NULL_STRING;
		*time += tempTime;
	}
}

void LangHandler::regulateDescription(string* description)
{
	eliminateSpaces(description);
}

void LangHandler::regulateLocation(string* location)
{
	eliminateSpaces(location);
}

void LangHandler::encoder(string input, Signal command) throw (string)
{
	log.writeEntered("LangHandler::encoder()");
	
	stringstream tempHolder(input);
	
	string date			= NULL_STRING;
	string time			= NULL_STRING;
	string index		= NULL_STRING;
	string description	= NULL_STRING;
	string location		= NULL_STRING;
	string priority		= NULL_STRING;

	//eliminate spaces first
	eliminateSpaces(&input);
	log.writeExecuted("eliminateSpaces");
	log.writeData("Input after eliminated spaces", input);
	
	//if empty string or string with all spaces is entered by user, exception
	//will be thrown and no more operation should be entertained
	if (input == NULL_STRING && command != EXIT_COMMAND && command != UNDO_COMMAND)
	{
		log.writeException("Empty command!");
		throw string ("Empty command!\n");
	} else
	{		
		//input format is different for different command
		switch (command)
		{
			//format will be "[date] [time] description [at location] [marked, unmarked]"
			case ADD_COMMAND:
				log.writeConditionEntered("add command separation", true);

				splitPriority(&input, &priority, ADD_MARK_INDICATOR, PRIORITY_INDICATOR);

				log.writeExecuted("LangHandler::splitPriority()");
				log.writeData("input", input);
				log.writeData("priority", priority);

				splitLocation(&input, &location);
				regulateLocation(&location);

				log.writeExecuted("LangHandler::splitLocation()");
				log.writeData("input", input);
				log.writeData("location", location);

				splitDate(&input, &date);
				regulateDate(&date);

				log.writeExecuted("LangHandler::splitDate()");
				log.writeData("input", input);
				log.writeData("date", date);

				splitTime(&input, &time, &date, true);
				regulateTime(&time);

				log.writeExecuted("LangHandler::splitTime()");
				log.writeData("input", input);
				log.writeData("time", time);

				splitDescription(&input, &description, false);
				regulateDescription(&description);

				log.writeExecuted("LangHandler::splitDescription()");
				log.writeData("input", input);
				log.writeData("description", description);

				break;

			//format will be "index"
			case DELETE_COMMAND:
				log.writeConditionEntered("delete command separation", true);
				
				splitIndex(&input, &index, false);

				log.writeExecuted("LangHandler::splitIndex()");
				log.writeData("input", input);
				log.writeData("index", index);				
				
				break;

			//format will be "index [date] [time] description [at location] [marked, unmarked]"
			case UPDATE_COMMAND:
				log.writeConditionEntered("edit command separation", true);

				splitIndex(&input, &index, true);

				log.writeExecuted("LangHandler::splitIndex()");
				log.writeData("input", input);
				log.writeData("index", index);

				splitPriority(&input, &priority, UPDATE_MARK_INDICATOR, PRIORITY_INDICATOR);

				log.writeExecuted("LangHandler::splitPriority()");
				log.writeData("input", input);
				log.writeData("priority", priority);

				splitPriority(&input, &priority, UPDATE_UNMARK_INDICATOR, SPACE_BAR);

				log.writeExecuted("LangHandler::splitPriority()");
				log.writeData("input", input);
				log.writeData("priority", priority);

				splitLocation(&input, &location);
				regulateLocation(&location);

				log.writeExecuted("LangHandler::splitLocation()");
				log.writeData("input", input);
				log.writeData("location", location);

				splitDate(&input, &date);
				regulateDate(&date);

				log.writeExecuted("LangHandler::splitDate()");
				log.writeData("input", input);
				log.writeData("date", date);

				splitTime(&input, &time, &date, false);
				regulateTime(&time);

				log.writeExecuted("LangHandler::splitTime()");
				log.writeData("input", input);
				log.writeData("time", time);

				splitDescription(&input, &description, true);
				regulateDescription(&description);

				log.writeExecuted("LangHandler::splitDescription()");
				log.writeData("input", input);
				log.writeData("description", description);
			
				break;

			//format will be "description", further decomposition will be handled by SearchExecutor
			case SEARCH_COMMAND:
				log.writeConditionEntered("search command separation", true);
				
				splitDescription(&input, &description, false);
				regulateDescription(&description);

				log.writeExecuted("LangHandler::splitDescription()");
				log.writeData("input", input);
				log.writeData("description", description);
				
				break;

			default:
				break;
		}

		details = DELIMINATOR + index + DELIMINATOR + description + DELIMINATOR + 
					location + DELIMINATOR + time + DELIMINATOR + date + DELIMINATOR + priority + DELIMINATOR;
	}
}

//@author A0088455R
/**
* Sets the command signal by checking user's command
**/
void LangHandler::setCommand(string userCommand)
{	
	//if user command is valid, set corresponding command type
	if ( userCommand == "add" )
	{
		command = ADD_COMMAND;
	}
	else
	if ( userCommand == "delete" )
	{
		command = DELETE_COMMAND;
	}
	else
	if ( userCommand == "update" )
	{
		command = UPDATE_COMMAND;
	}
	else
	if ( userCommand == "search" )
	{
		command = SEARCH_COMMAND;
	}
	else
	if (userCommand == "undo" )
	{
		command = UNDO_COMMAND;
	}
	else
	if (userCommand == "exit" )
	{
		command = EXIT_COMMAND;
	}
	else
	//if set command fails, no other operation should be entertained
	if (userCommand == "")
	{
		log.writeException("Possible commands: \"add\", \"delete\", \"search\", \"update\", \"undo\", \"exit\"");
		throw string ("Possible commands: \"add\", \"delete\", \"search\", \"update\", \"undo\", \"exit\"\n");
	}
	else
	{
		//if user command is invalid, command error signal should be set
		log.writeException("No Such Command\n");
		throw string ("No Such Command\n");
	}
}

LangHandler::LangHandler()
{
	//set default value for language handler status
	langStatus = CLEAR;
}

Signal LangHandler::getStatus()
{
	return langStatus;
}

//@author A0088455R
/**
* This method seperates user's input to command and raw string entry
* The encoder is envoked here to process the input
**/
void LangHandler::separate(string userInput) throw (string)
{
	log.writeEntered("LangHandler::separate()");
	
	stringstream tempHolder(userInput);

	string userCommand;
	string rawString;

	char dummySpace;

	//first we extract user command
	tempHolder >> userCommand;
	setCommand(userCommand);
	log.writeExecuted("LangHandler::setCommand()");
	log.writeData("userCommand", userCommand);
	
	//to get rid of leading space
	tempHolder.get(dummySpace);
	getline(tempHolder, rawString);

	encoder(rawString, command);
	log.writeExecuted("LangHandler::encoder()");
	log.writeData("details", details);
}

Executor* LangHandler::pack(bool* quit, Signal focusingField,
										vector<string>* generalEntryList,
										vector<string>* calendarEntryList,
										vector<string>* resultList,
										StorageHandler* store)
{
	assert(resultList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(store!=NULL);

	Executor* exe;
	
	switch (command)
	{
		case ADD_COMMAND:
			exe = new AddExecutor(generalEntryList, calendarEntryList, resultList, details);
			log.writeCreated("AddExecutor");
			
			break;

		case DELETE_COMMAND:
			exe = new DeleteExecutor(generalEntryList, calendarEntryList, details, focusingField);
			log.writeCreated("DeleteExecutor");
			
			break;

		case SEARCH_COMMAND:
			exe = new SearchExecutor(generalEntryList, calendarEntryList, resultList, details);
			log.writeCreated("SearchExecutor");
			
			break;

		case UPDATE_COMMAND:
			exe = new UpdateExecutor(generalEntryList, calendarEntryList, resultList, details, focusingField);
			log.writeCreated("UpdateExecutor");
			
			break;

		case EXIT_COMMAND:
			exe = new ExitExecutor(generalEntryList, calendarEntryList, store, quit);
			log.writeCreated("ExitExecutor");
			
			break;

		case UNDO_COMMAND:
			exe = NULL;
			log.writeCreated("NULL for undo command");
			
			break;

		default:
			break;
	}

	return exe;
}

LangHandler::~LangHandler()
{
}