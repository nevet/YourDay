#include <cassert>
#include <sstream>

#include "UI.h"

//@author A0088455R
const string UI::DID_U_KNOW_ADD = "To add an entry, type \"add\" followed by the desctription.\nFormat: DD/MM/YYYY HH:MM-HH:MM [DESCRIPTION] at [LOCATION] priority [high/mid/low]";
const string UI::DID_U_KNOW_DELETE = "To delete an entry, type \"delete\" followed by the index.\n i.e.: delete 5\nThe index is the index of selected active field";
const string UI::DID_U_KNOW_EXIT = "To exit, press Enter";
const string UI::DID_U_KNOW_SEARCH = "To search an entry, type \"search\" followed by the keyword(s). i.e.: search cs2103";
const string UI::DID_U_KNOW_UPDATE = "To update an entry, type \"update\" followed by the description.\nFormat: DD/MM/YYYY HH:MM-HH:MM [DESCRIPTION] at [LOCATION] priority [high/mid/low]";
const string UI::DID_U_KNOW_UNDO = "To undo the last operation press Enter";
const string UI::DID_U_KNOW_HINTS = "Possible commands: \"add\", \"delete\", \"search\", \"update\", \"undo\", \"exit\"";

void UI::setScreenSize()
{
    _COORD coord; 
    coord.X = WINDOWS_WIDTH; 
    coord.Y = WINDOWS_HEIGHT; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = WINDOWS_HEIGHT - 1; 
    Rect.Right = WINDOWS_WIDTH - 1; 

    // Get handle of the standard output 
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); 
    assert (Handle, NULL);
     
    // Set screen buffer size to that specified in coord 
    assert(SetConsoleScreenBufferSize(Handle, coord), false);
 
    // Set the window size to that specified in Rect 
    assert(SetConsoleWindowInfo(Handle, TRUE, &Rect), false);
}

//@author A0088455R
void UI::drawBanner()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	cout<<"                                                                                                                        ";
	cout<<"                                    ____  ____                _____                                                     ";
	cout<<"                                    \\  \\\\/  //                |   \\\\                                                    ";
	cout<<"                                     \\  \\\" //                 |    \\\\                                                   ";
	cout<<"                                      \\   // ____  __ __  ____| |\\ || ____ __  ___                                      ";
	cout<<"                                       | || /   \\\\| || ||| _//| |/ ||/   ||\\ \\/ //                                      ";
	cout<<"                                       | || | O ||| |/ ||| || |    //| o || \\  //                                       ";
	cout<<"                                       |_|| \\___// \\__// |_|| |___// \\___|| /_//                                        ";
	cout<<"                                                                                                                        ";
	cout<<"                                                                                                                        ";

}

void UI::drawCommandBox()
{
	gotoxy(0,COMMAND_INIT_Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4|FOREGROUND_INTENSITY);
	cout<<"command:";
	setBackground();
	cout<<"                                                                                                                ";
	cout<<"                                                                                                                        ";
	gotoxy(8,COMMAND_INIT_Y);
}

void UI::gotoCommandBox()
{
	gotoxy(8,COMMAND_INIT_Y);
}

void UI::setBackground()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void UI::clearBox(int startH, int height)
{
	//setBackground();
	gotoxy(0,startH);
	for (int i=0; i<height; i++)
		if (startH + height == WINDOWS_HEIGHT && i == height -1)
		{
			cout<<"                                                                                                                       ";
		}
		else
		{
			cout<<"                                                                                                                        ";
		}
	
	gotoxy(0,startH-1);
}

void UI :: gotoxy(int x, int y) //goes to x,y console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI::writeTitle(string words, int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),128);
	gotoxy(startX,startY);
	
	cout<<words<<endl;
	gotoxy(8+currentChar,COMMAND_INIT_Y);
	setBackground();
}

void UI::writeHighlightedTitle(string words,int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1|BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	gotoxy(startX,startY);

	cout<<words<<endl;
	gotoxy(8+currentChar,COMMAND_INIT_Y);
	setBackground();
}

void UI::highlightTitle(int searchBoxSize)
{
	switch (focusedField)
	{
	case GENERAL:
		writeHighlightedTitle("General: ", 1,0);
		writeTitle("Calendar: ", 1, CALENDAR_INIT_Y -2);	
		if (searchBoxSize != 0)
		{
			clearBox (COMMAND_INIT_Y +2, 1);
			writeTitle("SearchBox: ", 0, COMMAND_INIT_Y+2);
		}
		break;
	case CALENDAR:
		writeTitle("General: ", 1,0);
		writeHighlightedTitle("Calendar: ", 1, CALENDAR_INIT_Y -2);	
		if (searchBoxSize != 0)
		{
			clearBox (COMMAND_INIT_Y +2, 1);
			writeTitle("SearchBox: ", 0, COMMAND_INIT_Y+2);
		}
		break;
	case DIDUKNOW:
		writeTitle("General: ", 1,0);
		writeTitle("Calendar: ", 1, CALENDAR_INIT_Y -2);	
		if (searchBoxSize != 0)
		{
			clearBox (COMMAND_INIT_Y +2, 1);
			writeHighlightedTitle("SearchBox: ", 0, COMMAND_INIT_Y+2);
		}
		break;
	}
}

void UI::changeDisplayMode()
{	
	switch (focusedField)
	{
	case GENERAL:
		if (generalDisplayMode == DISPLAY_FULL)
		{
			generalDisplayMode = DISPLAY_PART;
		}
		else
		{
			generalDisplayMode = DISPLAY_FULL;
		}
		break;
	case CALENDAR:
		if (calendarDisplayMode == DISPLAY_FULL)
		{
			calendarDisplayMode = DISPLAY_PART;
		}
		else
		{
			calendarDisplayMode = DISPLAY_FULL;
		}
		break;
	}
}

void UI::displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	assert(resultList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	switch (focusedField)
	{
	case GENERAL:
		clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT);
		generalEntryListDisplay(generalEntryList);
		drawCommandBox();
		break;
	case CALENDAR:
		clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT);
		calendarEntryListDisplay(calendarEntryList);
		drawCommandBox();
		break;
	case DIDUKNOW:
		clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
		resultListDisplay(resultList, generalEntryList->size());
		drawCommandBox();
		break;
	default:
		assert (false);
	}
}

void UI::changeFocusedField(vector<string>* resultList)
{
	int sizeOfResultList = resultList->size();

	switch (focusedField)
	{
	case GENERAL:
		focusedField = CALENDAR;
		break;
	case CALENDAR:
		if (sizeOfResultList == 0)
		{
			focusedField = GENERAL;
		}
		else
		{
			focusedField = DIDUKNOW;
		}
		break;
	case DIDUKNOW:
		focusedField = GENERAL;
		clearBox(DIDUKNOW_INIT_Y,DIDUKNOW_HEIGHT+2);
		diduknowHintDisplay();
		break;
	default:
		assert(false);
	}
	highlightTitle(sizeOfResultList);
}

void UI::scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	assert(resultList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	switch (focusedField)
	{
	case GENERAL:
		if (generalInitRowIndex > GENERAL_BOX_HEIGHT)
		{
			generalInitRowIndex -= GENERAL_BOX_HEIGHT;
			clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT +1);
			generalEntryListDisplay(generalEntryList);
		}
		else if (generalInitRowIndex > 0)
		{
			generalInitRowIndex = 0;
			clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT +1);
			generalEntryListDisplay(generalEntryList);
		}
		
		break;
	case CALENDAR:
		if (calendarInitRowIndex > CALENDAR_BOX_HEIGHT)
		{
			calendarInitRowIndex -= CALENDAR_BOX_HEIGHT;
			clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT +1 );
			calendarEntryListDisplay(calendarEntryList);
		}
		else if (calendarInitRowIndex > 0)
		{
			calendarInitRowIndex = 0;
			clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT +1);
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex > RESULT_BOX_HEIGHT)
		{
			diduknowInitRowIndex -= RESULT_BOX_HEIGHT;
			clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
			resultListDisplay(resultList, generalEntryList->size());
		}
		else if (diduknowInitRowIndex > 0)
		{
			diduknowInitRowIndex = 0;
			clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
			resultListDisplay(resultList, generalEntryList->size());
		}

		break;
	default:
		assert (false);
	}
}

void UI::scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	assert(resultList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	int generalSize = generalEntryList->size();
	int calendarSize = calendarEntryList->size();
	int diduknowSize = resultList->size();

	switch (focusedField)
	{
	case GENERAL:
		if (generalEndRowIndex != generalSize -1)
		{
			generalInitRowIndex = generalEndRowIndex +1;
			clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT +1);
			generalEntryListDisplay(generalEntryList);
		}
		break;
	case CALENDAR:
		if (calendarEndRowIndex != calendarSize -1)
		{
			calendarInitRowIndex = calendarEndRowIndex +1;
			clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT + 1);
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case DIDUKNOW:
		if (diduknowEndRowIndex != diduknowSize -1)
		{
			diduknowInitRowIndex = diduknowEndRowIndex +1;
			clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
			resultListDisplay(resultList, generalSize);
		}
		break;
	default:
		assert (false);
	}
}

void UI::traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	assert(resultList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	diduknowStatus = DIDUKNOW_INIT;
	char keyIn;
	currentChar = 0;
	input = "";

	while ((keyIn = getch()) != ENTER)
	{
		switch (keyIn)
		{
		case -32:
			keyIn = getch();
			switch (keyIn)
			{
			case 72:
				scrollUp(calendarEntryList, generalEntryList, resultList);
				gotoxy(currentChar+8,COMMAND_INIT_Y);
				break;
			case 80:
				scrollDown(calendarEntryList, generalEntryList, resultList);
				gotoxy(currentChar+8,COMMAND_INIT_Y);
				break;
			case 73:
				changeDisplayMode();
				displayNewMode(calendarEntryList, generalEntryList, resultList);
				break;
			}
			break;
		case TAB:	
			changeFocusedField(resultList);
			break;
		case BACKSPACE:
			if (input.size()>0)
			{
				input = input.substr(0, input.size()-1);
				cout << "\b \b";
				if(currentChar>0)
				{
					--currentChar;
				}

				diduknowHintDisplay();
			}
			break;
		default:
			if (keyIn != ENTER && input.size() < MAX_INPUT_SIZE)
			{
				setBackground();
				cout << keyIn;
				input += keyIn;
				currentChar++;

				diduknowHintDisplay();
			}
			break;
		}
	}
}

//@author A0088455R
void UI::setDidUKnowStatus()
{
	if (input == "add")
	{
		diduknowStatus = ADD_COMMAND;
	}
	else if (input == "delete")
	{
		diduknowStatus = DELETE_COMMAND;

	}
	else if (input == "exit")
	{
		diduknowStatus = EXIT_COMMAND;
	}
	else if (input =="search")
	{
		diduknowStatus = SEARCH_COMMAND;
	}
	else if (input == "undo")
	{
		diduknowStatus = UNDO_COMMAND;
	}
	else if (input =="update")
	{
		diduknowStatus = EDIT_COMMAND;
	}
	else if (input == "")
	{
		diduknowStatus = DIDUKNOW_INIT;
	}
}

void UI::initializeDidUKnowStatus()
{
	diduknowPrevStatus = DIDUKNOW_CLEAR;
	diduknowStatus = DIDUKNOW_INIT;
}

void UI::initializeGeneralInitRowIndex(int generalSize)
{
	generalInitRowIndex = 0;
}

void UI::initializeCalendarInitRowIndex(int calendarSize)
{
	calendarInitRowIndex = 0;
}

void UI::initializeResultInitRowIndex(int resultSize)
{
	diduknowInitRowIndex = 0;
}

void UI::extractParts(string entry, string* partList)
{
	string part = "";
	char temp;
	int partCount = 0;

	for (int i =1; i<entry.length(); i++)
	{
		temp = entry[i];
		if (temp != '#')
		{
			part += temp;
		}
		else
		{
			partList[partCount] = part;
			partCount++;
			part = "";
		}
	}
}

void UI::printEntryPartMode(int* locationArray, int* colorArray, string* partArray, int index, int rowPosition)
{
	string part;
	int maxPartLength;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[0]);
	gotoxy(locationArray[0], rowPosition);
	cout<<index<<". ";


	for (int i = 1; i < NUMBER_OF_ENTRY_PARTS; i++)
	{
		part = partArray[i];
		maxPartLength = locationArray[i+1]- locationArray[i] -1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[i]);
		gotoxy(locationArray[i], rowPosition);

		if (part.length() >  maxPartLength)
			cout << part.substr(0, maxPartLength -3 ) << "...";
		else
			cout <<part;
	}
	cout <<endl;
}

void UI::printEntryFullMode(int* locationArray, int* colorArray, string* partArray, int index, int& RowPosition, bool& isPrinted)
{

}

void UI::splitPartToLines(string part, int maxLength, int& numberOfLines, vector<string>* lineVector)
{
	int initIndex = 0;
	numberOfLines = 0;

	for (int i = 0; i < part.length() / maxLength; i++) 
	{
		lineVector->push_back(part.substr(initIndex, maxLength));
		initIndex += maxLength;
		numberOfLines++;
	}

	if (part.length() % maxLength != 0)
	{
		lineVector->push_back(part.substr(initIndex, part.length() % maxLength));
		numberOfLines ++;
	}

}

bool UI::isEnoughSpace(int entryEnd, int spaceEnd)
{
	if (entryEnd > spaceEnd )
		return false;
	return true;
}

void UI::printCalendarEntry(int index, string entry, int &rowPosition, bool& isPrinted)
{
	assert(entry!= "");
	assert(rowPosition >= 0 && rowPosition <= WINDOWS_HEIGHT);

	int colorArray[NUMBER_OF_ENTRY_PARTS] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[NUMBER_OF_ENTRY_PARTS] = {CALENDAR_INDEX_INIT_X, CALENDAR_DESCRIPTION_INIT_X, CALENDAR_LOCATION_INIT_X,
		CALENDAR_TIME_INIT_X, CALENDAR_DATE_INIT_X, CALENDAR_PRIORITY_INIT_X};
	string partArray[NUMBER_OF_ENTRY_PARTS];
	extractParts(entry, partArray);

	switch (calendarDisplayMode)
	{
	case DISPLAY_PART:
		printEntryPartMode(locationArray, colorArray, partArray, index, rowPosition);
		break;
	case DISPLAY_FULL:

		break;
	default:
		assert(false);
		break;
	}
}

void UI::printGeneralEntry(int index, string entry, int &rowPosition, bool& isPrinted)
{
	assert(entry!= "");
	assert(rowPosition >= 0 && rowPosition <= WINDOWS_HEIGHT);

	int colorArray[NUMBER_OF_ENTRY_PARTS] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[NUMBER_OF_ENTRY_PARTS] = {GENERAL_INDEX_INIT_X, GENERAL_DESCRIPTION_INIT_X, GENERAL_LOCATION_INIT_X,
		GENERAL_TIME_INIT_X, GENERAL_DATE_INIT_X, GENERAL_PRIORITY_INIT_X};
	string partArray[NUMBER_OF_ENTRY_PARTS];
	extractParts(entry, partArray);

	switch (generalDisplayMode)
	{
	case DISPLAY_PART:
		printEntryPartMode(locationArray, colorArray, partArray, index, rowPosition);
		break;
	case DISPLAY_FULL:

		break;
	default:
		assert(false);
		break;
	}
}

void UI::printResultEntry(int index, string row, int &rowPosition, int sizeOfGeneral, bool& isPrinted)
{

}

//@author A0088455R
void UI::printDiduknowHints()
{
	clearBox(DIDUKNOW_INIT_Y,DIDUKNOW_HEIGHT+2);
	gotoxy(DIDUKNOW_INIT_X, DIDUKNOW_INIT_Y);
	switch (diduknowStatus)
	{
		case DIDUKNOW_INIT:
			{				
				cout<<DID_U_KNOW_HINTS;
				break;
			}
		case ADD_COMMAND:
			{
				cout<<DID_U_KNOW_ADD;
				break;
			}
		case DELETE_COMMAND:
			{
				cout<<DID_U_KNOW_DELETE;
				break;
			}
		case EXIT_COMMAND:
			{
				cout<<DID_U_KNOW_EXIT;
				break;
			}
		case SEARCH_COMMAND:
			{
				cout<<DID_U_KNOW_SEARCH;
				break;
			}
		case UNDO_COMMAND:
			{
				cout<<DID_U_KNOW_UNDO;
				break;
			}
		case EDIT_COMMAND:
			{
				cout<<DID_U_KNOW_UPDATE;
				break;
			}
		default:
			break;
	}
	diduknowPrevStatus=diduknowStatus;
	cout<<endl;
}

bool UI::isGeneral(string row)
{
	assert(row != "");

	//##CS2103 TUT#COM##Friday##
	bool ans;
	int countPart = 0;
	char c;
	int i = 0;
	while (countPart!= 4)
	{
		while ((c = row[i]) != '#')
		{
			i++;
		}
		i++;
		countPart++;
	}

	if (row[i+1] == '#')
	{
		ans = true;
	}
	else
	{
		ans = false;
	}
	return ans;
}

void UI::printContinueFooter()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOOTER_COLOR);
	printf(" ...");
}

void UI::generalEntryListDisplay(vector<string>* generalEntryList)
{	

	int sizeOfGeneral;
	int entryIndex;
	int rowPosition;
	string row;

	gotoxy(GENERAL_INIT_X, GENERAL_INIT_Y);
	sizeOfGeneral=generalEntryList->size();
	entryIndex = generalInitRowIndex;
	rowPosition = GENERAL_INIT_Y;
	bool isLastLineHasSpace = true;
	
	while (rowPosition < (CALENDAR_INIT_Y - CALENDAR_TITLE_HEIGHT) && entryIndex <sizeOfGeneral && isLastLineHasSpace)
	{
		row = generalEntryList ->at(entryIndex);
		printGeneralEntry(entryIndex + 1, row, rowPosition, isLastLineHasSpace);
		if (isLastLineHasSpace)
		{
			entryIndex ++;
			rowPosition ++;
		}
	}

	generalEndRowIndex = entryIndex -1;
	if (generalEndRowIndex != sizeOfGeneral -1)
	{
		gotoxy(0, rowPosition);
		printContinueFooter();
	}
}

void UI::calendarEntryListDisplay(vector<string>* calendarEntryList)
{

	int sizeOfCalendar;
	int entryIndex;
	int rowPosition;
	string row;
	bool isLastLineHasSpace = true;

	gotoxy(CALENDAR_INIT_X, CALENDAR_INIT_Y);
	sizeOfCalendar=calendarEntryList->size();
	entryIndex = calendarInitRowIndex;
	rowPosition = CALENDAR_INIT_Y;

	while (rowPosition < CALENDAR_INIT_Y + CALENDAR_BOX_HEIGHT && entryIndex <sizeOfCalendar && isLastLineHasSpace)
	{
		row = calendarEntryList ->at(entryIndex);
		printCalendarEntry(entryIndex + 1, row, rowPosition, isLastLineHasSpace);
		if (isLastLineHasSpace)
		{
			entryIndex ++;
			rowPosition ++;
		}
	}

	calendarEndRowIndex = entryIndex -1;
	if (calendarEndRowIndex != sizeOfCalendar -1)
	{
		gotoxy(0, rowPosition);
		printContinueFooter();
	}
}

void UI::resultListDisplay(vector<string>* resultList, int sizeOfGeneral)
{	
	assert(resultList!=NULL);

	int sizeOfDiduknow;
	int entryIndex;
	int rowPosition;
	string row;
	bool isLastLineHasSpace = true;
	
	gotoxy(OPERATION_RESULT_X, OPERATION_RESULT_Y);
	sizeOfDiduknow=resultList->size();
	entryIndex = diduknowInitRowIndex;
	
	if(resultList->size()>0)
	{
		clearBox(COMMAND_INIT_Y+5,1);
		highlightTitle(resultList->size());
	}

	gotoxy(1,OPERATION_RESULT_Y);
	rowPosition = OPERATION_RESULT_Y;
	while (rowPosition < WINDOWS_HEIGHT-1 && entryIndex <sizeOfDiduknow && isLastLineHasSpace)
	{
		row = resultList ->at(entryIndex);
		printResultEntry(entryIndex + 1, row, rowPosition, sizeOfGeneral, isLastLineHasSpace);
		if (isLastLineHasSpace)
		{
			entryIndex ++;
			rowPosition ++;
		}
	}
	
	diduknowEndRowIndex = entryIndex -1;
}

//@author A0088455R
void UI::diduknowHintDisplay()
{	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	setDidUKnowStatus();

	if (diduknowStatus != diduknowPrevStatus)
	{
		printDiduknowHints();
	}
	gotoxy(8+currentChar,COMMAND_INIT_Y);
}

//@author A0088455R
void UI::startingScreenDisplay()
{
	system("CLS");
	
	setScreenSize();

	drawBanner();
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"------------------------------------------------------------------------------------------------------------------------";
	cout<<"|                                        YourDay - always making your day :)                                           |";
	cout<<"------------------------------------------------------------------------------------------------------------------------";
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(50,18);
	cout<<"Press Enter to continue";

	char c;
	while ((c = getch()) != ENTER);
}

void UI::mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{	
	currentChar=0;
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(resultList!=NULL);
	setBackground();
	system("CLS");

	highlightTitle(resultList->size());

	generalEntryListDisplay(generalEntryList);
	calendarEntryListDisplay(calendarEntryList);
	initializeDidUKnowStatus();
	diduknowHintDisplay();
	resultListDisplay(resultList, generalEntryList->size());

	diduknowPrevStatus = CLEAR;
	drawCommandBox();
}

UI::UI(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	input = "";

	int generalSize = generalEntryList->size();
	int calendarSize = calendarEntryList ->size();
	int resultSize = resultList ->size();
	initializeGeneralInitRowIndex(generalSize);
	initializeCalendarInitRowIndex(calendarSize);
	initializeResultInitRowIndex(resultSize);

	generalDisplayMode = DISPLAY_PART;
	calendarDisplayMode = DISPLAY_PART;
	focusedField = GENERAL;	
	diduknowPrevStatus=DIDUKNOW_CLEAR;

	startingScreenDisplay();
	mainScreenDisplay( calendarEntryList, generalEntryList, resultList);
}

/*void UI::userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList, Signal status)
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(resultList!=NULL);

	curStatus = status;
	mainScreenDisplay(calendarEntryList, generalEntryList, resultList);
	traceInput(calendarEntryList, generalEntryList, resultList);
}
*/
string UI::retrieveInput()
{
	return input;
}

Signal UI::retrieveFocusedField()
{
	return focusedField;
}

void UI::displayMessage(string message)
{
	clearBox(DIDUKNOW_INIT_Y,BOTTOM_BOX_HEIGHT);
	gotoxy(0,DIDUKNOW_INIT_Y);
	setBackground();
	cout << message <<endl;
	drawCommandBox();
	diduknowPrevStatus = ERR;
}

UI::~UI()
{
}	 