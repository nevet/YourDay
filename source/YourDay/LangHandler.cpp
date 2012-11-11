/**
    YourDay
    LangHandler.cpp
    Purpose: Encodes user's input and decodes stored entry

    @author A0088455R
    @version 0.1 10/13/2012
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

void LangHandler::splitPriority(string* str, string* priority) throw (string)
{
	string input = *str;
	
	//add a space in front to avoid indicator missing
	input = SPACE_BAR + input;
	//check whether we have priority
	int pos = input.rfind(ADD_MARK_INDICATOR);
				
	//contains priority info
	if (pos != string::npos)
	{
		*priority = PRIORITY_INDICATOR;		
	} else
	{
		*priority = NULL_STRING;
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

	//contains location info
	if (pos != string::npos)
	{
		*location = getSuffix(input, pos + LOCATION_INDICATOR.length());
	} else
	{
		*location = NULL_STRING;
	}
	
	//get rid of location info
	input = getPrefix(input, pos);

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
	//exception; else if it is not even a date, date field should be set to
	//empty since nowhere else can find a date, and the input should remain
	//unchange.
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
	} else
	{
		*date = NULL_STRING;
	}

	*str = input;
}

void LangHandler::splitTime(string* str, string* time, string* date) throw (string)
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
	//exception; else if it is not even a time, date field should be set to
	//empty since nowhere else can find a time, and the input should remain
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
	} else
	{
		*time = NULL_STRING;
	}

	//if date field is omitted with time field specified, we will auto-fill the
	//date field with current date
	if (!time->empty() && date->empty())
	{
		fillUpDate(date);
		log.writeData("date after auto fill up", date);
	}

	*str = input;
}

void LangHandler::splitDescription(string* str, string* description) throw (string)
{
	*description = *str;
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

	string temp;

	size_t pos;

	//eliminate spaces first
	eliminateSpaces(&input);
	log.writeExecuted("eliminateSpaces");
	log.writeData("Input after eliminated spaces", input);
	
	//if empty string or string with all spaces is entered by user, exception
	//will be thrown and no more operation should be entertained
	if (input == NULL_STRING && command != EXIT_COMMAND && command != UNDO_COMMAND)
	{
		log.writeException("The length entered exceeds the available range");
		throw string ("The length entered exceeds the available range\n");
	} else
	{		
		//input format is different for different command
		switch (command)
		{
			//format will be "[date] [time] description [at location] [marked, unmarked]"
			case ADD_COMMAND:
				log.writeConditionEntered("add command separation", true);

				splitPriority(&input, &priority);

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

				splitTime(&input, &time, &date);
				regulateTime(&time);

				log.writeExecuted("LangHandler::splitTime()");
				log.writeData("input", input);
				log.writeData("time", time);

				splitDescription(&input, &description);
				regulateDescription(&description);

				log.writeExecuted("LangHandler::splitDescription()");
				log.writeData("input", input);
				log.writeData("description", description);

				break;

			//format will be "index"
			case DELETE_COMMAND:
				log.writeConditionEntered("delete command separation", true);
				
				log.writeData("Input eliminates spaces", input);
				pos = input.find(SPACE_BAR);
				
				if (pos == string::npos)
				{
					index = input.substr(0, input.length());
					log.writeExecuted("delete command separation/index separation");
					
					if (!isInt(index))
					{
						index = NULL_STRING;
						
						log.writeException("Index error");
						throw string ("Index error\n");
					}
				}
				else
				{
					log.writeException("Input error");
					throw string("Input error\n");
				}
				
				break;

			//format will be "index [date] [time] description [at location] [priority [high, mid, low]]"
			case UPDATE_COMMAND:
				log.writeConditionEntered("edit command separation", true);
				
				pos = input.find(SPACE_BAR);
				
				if (pos == string::npos)
				{
					log.writeException("edit format error");
					throw string ("edit format error\n");
				} else
				{
					index = input.substr(0, pos);
					log.writeData("index", index);
					log.writeExecuted("edit command separation/index separation");
					
					if (!isInt(index))
					{
						index = NULL_STRING;

						log.writeException("Index error");
						throw string ("Index error\n");
					} else
					{
						//get rid of index info
						input = input.substr(pos + 1);
						eliminateSpaces(&input);
						log.writeData("Input after eliminated spaces", input);
						
						input = " " + input;
						//check whether we have priority
						pos = input.rfind(UPDATE_MARK_INDICATOR);

						if (pos != string::npos)
						{
							priority = "*";
							//get rid of priority info
							input = input.substr(0, pos);
						}

						pos = input.rfind(UPDATE_UNMARK_INDICATOR);

						if (pos != string::npos)
						{
							priority = " ";
							//get rid of priority info
							input = input.substr(0, pos);
						}

						eliminateSpaces(&input);
						log.writeData("Input after eliminated spaces", input);
						log.writeExecuted("edit command separation/priority separation");

						input = " " + input;
						//check whether we have location
						pos = input.rfind(LOCATION_INDICATOR);
						//contains location info
						if (pos != string::npos)
						{
							location = input.substr(pos + LOCATION_INDICATOR.length());
							eliminateSpaces(&location);
							//get rid of location info
							input = input.substr(0, pos);
						}
						
						eliminateSpaces(&input);
						log.writeData("Input after eliminated spaces", input);
						log.writeExecuted("edit command separation/location separation");
						
						pos = input.find(SPACE_BAR);

						if (pos != string::npos)
						{
							//extract potential date information and exmaine it
							date = input.substr(0, pos);
						} else
						{
							date = input;
						}
				
						//only if date field is not empty
						if (isDate(date))
						{
							if (pos != string::npos)
							{
								input = input.substr(pos + 1);
								
								eliminateSpaces(&input);
								log.writeData("Input after eliminated spaces", input);

								pos = input.find(SPACE_BAR);
					
								if (pos != string::npos)
								{
									time = input.substr(0, pos);
								} else
								{
									time = input;
								}

								if (isTime(time))
								{
									if (pos != string::npos)
									{
										input = input.substr(pos + 1);
									} else
									{
										input = NULL_STRING;
									}
								} else
								{
									time = NULL_STRING;
								}
							} else
							{
								input = NULL_STRING;
							}
						} else
						{
							//it might be a time, so we need to exmaine it
							time = date;
							date = NULL_STRING;

							if (isTime(time))
							{
								if (pos != string::npos)
								{
									input = input.substr(pos + 1);
								} else
								{
									input = NULL_STRING;
								}
							} else
							{
								time = NULL_STRING;
							}
						}
				
						log.writeExecuted("add command separation/date and time separtation");

						eliminateSpaces(&input);
						log.writeData("Input after eliminated spaces", input);

						description = input;
						
						//after have done separating, we need to exmaine each field
						//to make sure they are logic, if applicable
						if (!date.empty())
						{
							if (!isLogicDate(date))
							{
								log.writeException("date error");
								throw string ("date error\n");
							} else
							{
								regulateDate(&date);
							}
						}

						if (!time.empty())
						{
							if (!isLogicTime(time))
							{
								log.writeException("time error");
								throw string ("time error\n");
							} else
							{
								regulateTime(&time);
							}
						}
					}
				}
			
				break;

			//format will be "description", further decomposition will be handled by SearchExecutor
			case SEARCH_COMMAND:
				log.writeConditionEntered("search command separation", true);
				
				description = input;
				
				log.writeData("description", input);
				log.writeExecuted("search command separation/description saperated");
				
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