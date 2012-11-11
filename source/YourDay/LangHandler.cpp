/**
    YourDay
    LangHandler.cpp
    Purpose: Encodes user's input and decodes stored entry

    @author A0088455R
    @version 0.1 10/13/2012
*/

#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <ctime>
#include <cassert>

#include "LangHandler.h"

const int LangHandler::MONTH[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const string LangHandler::NULL_STRING = "";
const string LangHandler::PRIORITY_INDICATOR = " priority ";
const string LangHandler::LOCATION_INDICATOR = " at ";
const string LangHandler::SPACE_BAR = " ";
const string LangHandler::DELIMINATOR = "#";

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
	int year, month, day;

	return sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) == 3;
}

bool LangHandler::isTime(string time)
{
	int h1, h2, m1, m2;

	return sscanf(time.c_str(), "%d:%d-%d:%d", &h1, &m1, &h2, &m2) == 4;
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

bool LangHandler::isLogicPriority(string priority)
{
	return (priority == "high") || (priority == "mid") || (priority == "low");
}

void LangHandler::eliminateSpaces(string& str)
{
	int len = str.length();
	
	int lead = 0;
	int trail = len-1;

	if (!str.empty())
	{
		while (lead <= trail && str[lead] == ' ')
		{
			lead++;
		}

		while (trail >= lead && str[trail] == ' ')
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
}

void LangHandler::encoder(string input, Signal command)
{
	log.writeEntered("LangHandler::encoder()");
	
	stringstream tempHolder(input);
	
	string date = NULL_STRING;
	string time = NULL_STRING;
	string index = NULL_STRING;
	string description = NULL_STRING;
	string location = NULL_STRING;
	string priority = NULL_STRING;

	string temp;

	size_t pos;

	//eliminate spaces first
	eliminateSpaces(input);
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
			//format will be "[date] [time] description [at location] [priority [high, mid, low]]"
			case ADD_COMMAND:
				log.writeConditionEntered("add command separation", true);
				
				//add a space in front to avoid indicator missing
				input = " " + input;
				//check whether we have priority
				pos = input.rfind(PRIORITY_INDICATOR);
				//contains priority info
				if (pos != string::npos)
				{
					priority = input.substr(pos + PRIORITY_INDICATOR.length());
					eliminateSpaces(priority);
					//get rid of priority info
					input = input.substr(0, pos);
				}

				//backtrack
				eliminateSpaces(input);
				log.writeData("Input after eliminated spaces", input);
				log.writeExecuted("add command separation/priority separation");

				//add a space before the string in case "at " happens
				input = " " + input;
				//check whether we have location
				pos = input.rfind(LOCATION_INDICATOR);
				//contains location info
				if (pos != string::npos)
				{
					location = input.substr(pos + LOCATION_INDICATOR.length());
					eliminateSpaces(location);
					//get rid of location info
					input = input.substr(0, pos);
				}
				
				//backtrack
				eliminateSpaces(input);
				log.writeData("Input after eliminated spaces", input);
				log.writeExecuted("add command separation/locatoin separation");

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
						
						//get rid of possible redundant spaces between date and time field
						eliminateSpaces(input);
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
				
				eliminateSpaces(input);
				log.writeData("Input after eliminated spaces", input);

				description = input;

				//after have done separating, we need to exmaine each field
				//to make sure they are logic, if applicable
				if (description.empty() && (!priority.empty() || !date.empty() || !time.empty() || !location.empty()))
				{
					log.writeException("empty description error");
					throw string ("empty description error\n");
				}
				if (!priority.empty() && !isLogicPriority(priority))
				{
					log.writeException("priority error");
					throw string ("priority error\n");
				} else
				if (!date.empty() && !isLogicDate(date))
				{
					log.writeException("date error");
					throw string ("date error\n");
				} else
				if (!time.empty() && !isLogicTime(time))
				{
					log.writeException("time error");
					throw string ("time error\n");
				}

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
			case EDIT_COMMAND:
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
						eliminateSpaces(input);
						log.writeData("Input after eliminated spaces", input);
						
						input = " " + input;
						//check whether we have priority
						pos = input.rfind(PRIORITY_INDICATOR);
						//contains priority info
						if (pos != string::npos)
						{
							priority = input.substr(pos + PRIORITY_INDICATOR.length());
							eliminateSpaces(priority);
							//get rid of priority info
							input = input.substr(0, pos);
						}
						
						eliminateSpaces(input);
						log.writeData("Input after eliminated spaces", input);
						log.writeExecuted("edit command separation/priority separation");

						input = " " + input;
						//check whether we have location
						pos = input.rfind(LOCATION_INDICATOR);
						//contains location info
						if (pos != string::npos)
						{
							location = input.substr(pos + LOCATION_INDICATOR.length());
							eliminateSpaces(location);
							//get rid of location info
							input = input.substr(0, pos);
						}
						
						eliminateSpaces(input);
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
								
								eliminateSpaces(input);
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

						eliminateSpaces(input);
						log.writeData("Input after eliminated spaces", input);

						description = input;
						
						//after have done separating, we need to exmaine each field
						//to make sure they are logic, if applicable
						if (!priority.empty() && !isLogicPriority(priority))
						{
							log.writeException("priority error");
							throw string ("priority error\n");
						} else
						if (!date.empty() && !isLogicDate(date))
						{
							log.writeException("date error");
							throw string ("date error\n");
						} else
						if (!time.empty() && !isLogicTime(time))
						{
							log.writeException("time error");
							throw string ("time error\n");
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
		command = EDIT_COMMAND;
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

		case EDIT_COMMAND:
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