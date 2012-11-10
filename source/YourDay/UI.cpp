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
			printResultFooter();
		}
		break;
	case CALENDAR:
		writeTitle("General: ", 1,0);
		writeHighlightedTitle("Calendar: ", 1, CALENDAR_INIT_Y -2);	
		if (searchBoxSize != 0)
		{
			clearBox (COMMAND_INIT_Y +2, 1);
			writeTitle("SearchBox: ", 0, COMMAND_INIT_Y+2);
			printResultFooter();
		}
		break;
	case SEARCH_RESULT:
		writeTitle("General: ", 1,0);
		writeTitle("Calendar: ", 1, CALENDAR_INIT_Y -2);	
		if (searchBoxSize != 0)
		{
			clearBox (COMMAND_INIT_Y +2, 1);
			writeHighlightedTitle("SearchBox: ", 0, COMMAND_INIT_Y+2);
			printResultFooter();
		}
		break;
	}
}

void UI::changeDisplayMode()
{	
	switch (focusedField)
	{
	case GENERAL:
		if (generalDisplayMode == FULL_MODE)
		{
			generalDisplayMode = PART_MODE;
		}
		else
		{
			generalDisplayMode = FULL_MODE;
		}
		break;
	case CALENDAR:
		if (calendarDisplayMode == FULL_MODE)
		{
			calendarDisplayMode = PART_MODE;
		}
		else
		{
			calendarDisplayMode = FULL_MODE;
		}
		break;
	case SEARCH_RESULT:
		if (resultDisplayMode == FULL_MODE)
		{
			resultDisplayMode = PART_MODE;
		}
		else
		{
			resultDisplayMode = FULL_MODE;
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
	case SEARCH_RESULT:
		clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
		resultListDisplay(resultList);
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
			focusedField = SEARCH_RESULT;
		}
		break;
	case SEARCH_RESULT:
		focusedField = GENERAL;
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
		if (indexCurGeneralInitArray > 0)
		{
			indexCurGeneralInitArray --;
			clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT +1);
			generalEntryListDisplay(generalEntryList);
		}
		break;
	case CALENDAR:
		if (indexCurCalendarInitArray > 0)
		{	
			indexCurCalendarInitArray --;
			clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT +1 );
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case SEARCH_RESULT:
		if (indexCurResultInitArray > 0)
		{
			indexCurResultInitArray --;
			clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
			resultListDisplay(resultList);
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

	bool isValid;

	switch (focusedField)
	{
	case GENERAL:
		getNextGeneralInitIndex(isValid);
		if (isValid)
		{	
			indexCurGeneralInitArray ++ ;
			clearBox(GENERAL_INIT_Y, GENERAL_BOX_HEIGHT +1);
			generalEntryListDisplay(generalEntryList);
		}
		break;
	case CALENDAR:
		getNextCalendarInitIndex(isValid);
		if (isValid)
		{
			indexCurCalendarInitArray ++;
			clearBox(CALENDAR_INIT_Y, CALENDAR_BOX_HEIGHT + 1);
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case SEARCH_RESULT:
		getNextResultInitIndex(isValid);
		if (isValid)
		{
			indexCurResultInitArray ++;
			clearBox(OPERATION_RESULT_Y, RESULT_BOX_HEIGHT);
			resultListDisplay(resultList);
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
	else if ((diduknowStatus == ADD_COMMAND && input.find("add")) ||
			(diduknowStatus == DELETE_COMMAND &&  input.find("delete")) ||
			(diduknowStatus == EXIT_COMMAND && input.find("edit")) ||
			(diduknowStatus == SEARCH_COMMAND && input.find("search")) ||
			(diduknowStatus == UNDO_COMMAND && input.find("undo")) ||
			(diduknowStatus == EDIT_COMMAND && input.find("edit")))
	{
		diduknowStatus = DIDUKNOW_INIT;
	}
}

void UI::initializeDidUKnowStatus()
{
	diduknowPrevStatus = DIDUKNOW_CLEAR;
	diduknowStatus = DIDUKNOW_INIT;
}

void UI::initializeInitArrayIndices()
{
	indexCurCalendarInitArray = 0;
	indexCurGeneralInitArray = 0;
	indexCurResultInitArray = 0;
}

void UI::initializeDisplayModes()
{
	generalDisplayMode = FULL_MODE;
	calendarDisplayMode = FULL_MODE;
	resultDisplayMode = FULL_MODE;
	focusedField = GENERAL;	
}

void UI::initializeFocusedField()
{
	focusedField = GENERAL;	
}

void UI::setInitialIndexArrays(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	generalInitArrayPart.clear();
	generalInitArrayFull.clear();
	calendarInitArrayPart.clear();
	calendarInitArrayFull.clear();
	resultInitArrayPart.clear();
	resultInitArrayFull.clear();

	setGeneralInitArrayPart(generalEntryList);
	setGeneralInitArrayFull(generalEntryList);
	setCalendarInitArrayPart(calendarEntryList);
	setCalendarInitArrayFull(calendarEntryList);
	setResultInitArrayPart(resultList);
	setResultInitArrayFull(resultList);
}

int UI::getGeneralInitIndex()
{
	int ans;

	switch (generalDisplayMode)
	{
	case PART_MODE:
		ans = generalInitArrayPart[indexCurGeneralInitArray];
		break;
	case FULL_MODE:
		ans = generalInitArrayFull[indexCurGeneralInitArray];
		break;
	}
	return ans;
}

int UI::getNextGeneralInitIndex(bool& isValid)
{
	int ans = -1;

	switch (generalDisplayMode)
	{
	case PART_MODE:
		if (indexCurGeneralInitArray < generalInitArrayPart.size() -1)
		{
			ans = generalInitArrayPart[indexCurGeneralInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	case FULL_MODE:
		if (indexCurGeneralInitArray < generalInitArrayFull.size() -1)
		{
			ans = generalInitArrayFull[indexCurGeneralInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	}
	return ans;
}
int UI::getCalendarInitIndex()
{
	int ans;

	switch (calendarDisplayMode)
	{
	case PART_MODE:
		ans = calendarInitArrayPart[indexCurCalendarInitArray];
		break;
	case FULL_MODE:
		ans = calendarInitArrayFull[indexCurCalendarInitArray];
		break;
	}
	return ans;
}

int UI::getNextCalendarInitIndex(bool& isValid)
{
	int ans = -1;

	switch (calendarDisplayMode)
	{
	case PART_MODE:
		if (indexCurCalendarInitArray < calendarInitArrayPart.size() -1)
		{
			ans = calendarInitArrayPart[indexCurCalendarInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	case FULL_MODE:
		if (indexCurCalendarInitArray < calendarInitArrayFull.size() -1)
		{
			ans = calendarInitArrayFull[indexCurCalendarInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	}
	return ans;
}

int UI::getResultInitIndex()
{
	int ans;

	switch (resultDisplayMode)
	{
	case PART_MODE:
		ans = resultInitArrayPart[indexCurResultInitArray];
		break;
	case FULL_MODE:
		ans = resultInitArrayFull[indexCurResultInitArray];
		break;
	}
	return ans;
}

int UI::getNextResultInitIndex(bool& isValid)
{
	int ans = -1;

	switch (resultDisplayMode)
	{
	case PART_MODE:
		if (indexCurResultInitArray < resultInitArrayPart.size() -1)
		{
			ans = resultInitArrayPart[indexCurResultInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	case FULL_MODE:
		if (indexCurResultInitArray < resultInitArrayFull.size() -1)
		{
			ans = resultInitArrayFull[indexCurResultInitArray +1];
			isValid = true;
		}
		else
		{
			isValid = false;
		}
		break;
	}
	return ans;
}

int UI::findNearestInitArrayIndex(int rowIndex)
{
	int ans;
	switch (focusedField)
	{
		case CALENDAR:
	for (int i = 0; i < )
	}

	return ans;
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

int UI::countPartLine(string part, int maxLength)
{
	int initIndex = 0;
	int ans = 0;

	for (int i = 0; i < part.length() / maxLength; i++) 
	{
		ans++;
		initIndex += maxLength;
	}

	if (part.length() % maxLength != 0)
	{
		ans ++;
	}

	return ans;
}

void UI::setGeneralInitArrayPart(vector<string>* generalEntryList)
{
	int index = 0;
	int generalSize = generalEntryList ->size();

	while (index < generalSize)
	{
		generalInitArrayPart.push_back(index);
		index += GENERAL_BOX_HEIGHT;
	}
}

void UI::setGeneralInitArrayFull(vector<string>* generalEntryList)
{
	int generalSize = generalEntryList->size();
	string row;
	string description;
	string location;
	int descriptionLength;
	int locationLength;
	int descriptionMaxLength = GENERAL_LOCATION_INIT_X - GENERAL_DESCRIPTION_INIT_X -1;
	int locationMaxLength = GENERAL_DATE_INIT_X - GENERAL_LOCATION_INIT_X -1;
	int lineOccupied;
	string partArray[NUMBER_OF_ENTRY_PARTS];

	int index = 0;
	int countLine = 0;

	for (int i =0; i < generalSize; i++)
	{
		row = generalEntryList->at(i);
		extractParts(row, partArray);
		description = partArray[1];
		location = partArray [2];
		
		descriptionLength = countPartLine(description, descriptionMaxLength);
		locationLength = countPartLine(location, locationMaxLength);
		lineOccupied = max(descriptionLength, locationLength);

		countLine += lineOccupied;
		if (countLine > GENERAL_BOX_HEIGHT)		
		{
			generalInitArrayFull.push_back(index);
			countLine = lineOccupied;
			index = i;
		}
	}
	generalInitArrayFull.push_back(index);
}

void UI::setCalendarInitArrayPart(vector<string>* calendarEntryList)
{
	int index = 0;
	int calendarSize = calendarEntryList ->size();

	while (index < calendarSize)
	{
		calendarInitArrayPart.push_back(index);
		index += CALENDAR_BOX_HEIGHT;
	}
}

void UI::setCalendarInitArrayFull(vector<string>* calendarEntryList)
{
	int calendarSize = calendarEntryList->size();
	string row;
	string description;
	string location;
	int descriptionLength;
	int locationLength;
	int descriptionMaxLength = CALENDAR_LOCATION_INIT_X - CALENDAR_DESCRIPTION_INIT_X -1;
	int locationMaxLength = CALENDAR_DATE_INIT_X - CALENDAR_LOCATION_INIT_X -1;
	int lineOccupied;
	string partArray[NUMBER_OF_ENTRY_PARTS];

	int index = 0;
	int countLine = 0;

	for (int i =0; i < calendarSize; i++)
	{
		row = calendarEntryList->at(i);
		extractParts(row, partArray);
		description = partArray[1];
		location = partArray [2];

		descriptionLength = countPartLine(description, descriptionMaxLength);
		locationLength = countPartLine(location, locationMaxLength);
		lineOccupied = max(descriptionLength, locationLength);

		countLine += lineOccupied;
		if (countLine > CALENDAR_BOX_HEIGHT)		
		{
			calendarInitArrayFull.push_back(index);
			countLine = lineOccupied;
			index = i;
		}
	}
	calendarInitArrayFull.push_back(index);
}

void UI::setResultInitArrayPart(vector<string>* resultList)
{
	int index = 0;
	int resultSize = resultList ->size();

	while (index < resultSize)
	{
		resultInitArrayPart.push_back(index);
		index += RESULT_BOX_HEIGHT;
	}
}

void UI::setResultInitArrayFull(vector<string>* resultList)
{
	int resultSize = resultList->size();
	string row;
	string description;
	string location;
	int descriptionLength;
	int locationLength;
	int descriptionMaxLength;
	int locationMaxLength;
	int lineOccupied;
	string partArray[NUMBER_OF_ENTRY_PARTS];

	int index = 0;
	int countLine = 0;

	for (int i =0; i < resultSize; i++)
	{
		row = resultList->at(i);
		extractParts(row, partArray);
		description = partArray[1];
		location = partArray [2];

		if (isGeneral(row))
		{	
			descriptionMaxLength = GENERAL_LOCATION_INIT_X - GENERAL_DESCRIPTION_INIT_X -1;
			locationMaxLength = GENERAL_DATE_INIT_X - GENERAL_LOCATION_INIT_X -1;
		}
		else
		{
			descriptionMaxLength = CALENDAR_LOCATION_INIT_X - CALENDAR_DESCRIPTION_INIT_X -1;
			locationMaxLength = CALENDAR_DATE_INIT_X - CALENDAR_LOCATION_INIT_X -1;
		}

		descriptionLength = countPartLine(description, descriptionMaxLength);
		locationLength = countPartLine(location, locationMaxLength);
		lineOccupied = max(descriptionLength, locationLength);

		countLine += lineOccupied;
		if (countLine > RESULT_BOX_HEIGHT)		
		{
			resultInitArrayFull.push_back(index);
			countLine = lineOccupied;
			index = i;
		}
	}
	resultInitArrayFull.push_back(index);
}

void UI::printLimitedLengthPart(string part, int maxLength, int initX, int initY, int& endPosition)
{
	int initIndex = 0;
	int curLine = initY;

	for (int i = 0; i < part.length() / maxLength; i++) 
	{
		gotoxy(initX, curLine);
		cout<< part.substr(initIndex, maxLength);
		curLine ++;
		initIndex += maxLength;
	}

	if (part.length() % maxLength != 0)
	{
		gotoxy(initX, curLine);
		cout<< part.substr(initIndex, part.length() % maxLength);
		curLine ++;
	}

	endPosition = curLine -1;
}

void UI::printEntryPartMode(int* positionArray, int* colorArray, string* partArray, int index, int rowPosition)
{
	string part;
	int maxPartLength;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[0]);
	gotoxy(positionArray[0], rowPosition);
	cout<<index<<". ";


	for (int i = 1; i < NUMBER_OF_ENTRY_PARTS; i++)
	{
		part = partArray[i];
		maxPartLength = positionArray[i+1]- positionArray[i] -1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[i]);
		gotoxy(positionArray[i], rowPosition);

		if (part.length() >  maxPartLength)
			cout << part.substr(0, maxPartLength -3 ) << "...";
		else
			cout <<part;
	}
	cout <<endl;
}

void UI::printEntryFullMode(int* positionArray, int* colorArray, string* partArray, int index, int& rowPosition)
{
	string description = partArray[1];
	string location = partArray[2];
	int descriptionLength;
	int locationLength;
	int descriptionMaxLength = positionArray[2] - positionArray[1] -1;
	int locationMaxLength = positionArray[3]- positionArray[2] -1;
	int descriptionEnd;
	int locationEnd;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[0]);
	gotoxy(positionArray[0], rowPosition);
	cout<<index<<". ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[1]);
	printLimitedLengthPart(description, descriptionMaxLength, positionArray[1], rowPosition, descriptionEnd);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[2]);
	printLimitedLengthPart(location, locationMaxLength, positionArray[2], rowPosition, locationEnd);

	for (int i = 3; i< NUMBER_OF_ENTRY_PARTS; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[i]);
		gotoxy(positionArray[i], rowPosition);
		cout << partArray[i];
	}

	rowPosition = max(descriptionEnd, locationEnd);
}

void UI::printCalendarEntry(int index, string entry, int& rowPosition)
{
	assert(entry!= "");
	assert(rowPosition >= 0 && rowPosition <= WINDOWS_HEIGHT);

	int colorArray[NUMBER_OF_ENTRY_PARTS] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int positionArray[NUMBER_OF_ENTRY_PARTS] = {CALENDAR_INDEX_INIT_X, CALENDAR_DESCRIPTION_INIT_X, CALENDAR_LOCATION_INIT_X,
		CALENDAR_TIME_INIT_X, CALENDAR_DATE_INIT_X, CALENDAR_PRIORITY_INIT_X};
	string partArray[NUMBER_OF_ENTRY_PARTS];
	extractParts(entry, partArray);

	switch (calendarDisplayMode)
	{
	case PART_MODE:
		printEntryPartMode(positionArray, colorArray, partArray, index, rowPosition);
		break;
	case FULL_MODE:
		printEntryFullMode(positionArray, colorArray, partArray, index, rowPosition);
		break;
	default:
		assert(false);
		break;
	}
}

void UI::printGeneralEntry(int index, string entry, int& rowPosition)
{
	assert(entry!= "");
	assert(rowPosition >= 0 && rowPosition <= WINDOWS_HEIGHT);

	int colorArray[NUMBER_OF_ENTRY_PARTS] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int positionArray[NUMBER_OF_ENTRY_PARTS] = {GENERAL_INDEX_INIT_X, GENERAL_DESCRIPTION_INIT_X, GENERAL_LOCATION_INIT_X,
		GENERAL_TIME_INIT_X, GENERAL_DATE_INIT_X, GENERAL_PRIORITY_INIT_X};
	string partArray[NUMBER_OF_ENTRY_PARTS];
	extractParts(entry, partArray);

	switch (generalDisplayMode)
	{
	case PART_MODE:
		printEntryPartMode(positionArray, colorArray, partArray, index, rowPosition);
		break;
	case FULL_MODE:
		printEntryFullMode(positionArray, colorArray, partArray, index, rowPosition);
		break;
	default:
		assert(false);
		break;
	}
}

void UI::printResultEntry(int index, string row, int &rowPosition)
{
	Signal temp;

	if (isGeneral(row))
	{
		temp = generalDisplayMode;
		generalDisplayMode = resultDisplayMode;

		printGeneralEntry(index, row, rowPosition);

		generalDisplayMode = temp;
	}
	else
	{
		temp = calendarDisplayMode;
		calendarDisplayMode = resultDisplayMode;

		printCalendarEntry(index, row, rowPosition);

		calendarDisplayMode = temp;
	}
}

//@author A0088455R
void UI::printDiduknowHints()
{
	clearBox(DIDUKNOW_INIT_Y,BOTTOM_BOX_HEIGHT);
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

void UI::printGeneralFooter()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOOTER_COLOR);
	gotoxy(15, GENERAL_INIT_Y - 2);
	switch (generalDisplayMode)
	{
	case PART_MODE:
		cout << "Page " << indexCurGeneralInitArray + 1 << "/" << generalInitArrayPart.size();
		break;
	case FULL_MODE:
		cout << "Page " << indexCurGeneralInitArray + 1 << "/" << generalInitArrayFull.size();
		break;
	}
}

void UI::printCalendarFooter()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOOTER_COLOR);
	gotoxy(15, CALENDAR_INIT_Y -2);
	switch (calendarDisplayMode)
	{
	case PART_MODE:
		cout << "Page" << indexCurCalendarInitArray + 1 << "/" << calendarInitArrayPart.size();
		break;
	case FULL_MODE:
		cout << "Page" << indexCurCalendarInitArray + 1<< "/" << calendarInitArrayFull.size();
		break;
	}
}

void UI::printResultFooter()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOOTER_COLOR);
	gotoxy(15, COMMAND_INIT_Y +2);
	switch (resultDisplayMode)
	{
	case PART_MODE:
		cout << "Page" << indexCurResultInitArray + 1 << "/" << resultInitArrayPart.size();
		break;
	case FULL_MODE:
		cout << "Page" << indexCurResultInitArray + 1<< "/" << resultInitArrayFull.size();
		break;
	}
}

void UI::generalEntryListDisplay(vector<string>* generalEntryList)
{	
	int sizeOfGeneral = generalEntryList->size();
	int entryIndex = getGeneralInitIndex();
	bool isValid = true;
	int nextInitIndex = getNextGeneralInitIndex(isValid);
	int rowPosition = GENERAL_INIT_Y;
	string row;

	gotoxy(GENERAL_INIT_X, GENERAL_INIT_Y);
	
	while ((isValid && entryIndex < nextInitIndex) || (!isValid && entryIndex < sizeOfGeneral))
	{
		row = generalEntryList ->at(entryIndex);
		printGeneralEntry(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}

	printGeneralFooter();
}

void UI::calendarEntryListDisplay(vector<string>* calendarEntryList)
{
	int sizeOfCalendar = calendarEntryList->size();
	int entryIndex = getCalendarInitIndex();
	bool isValid = true;
	int nextInitIndex = getNextCalendarInitIndex(isValid);
	int rowPosition = CALENDAR_INIT_Y;
	string row;

	gotoxy(CALENDAR_INIT_X, CALENDAR_INIT_Y);

	while ((isValid && entryIndex < nextInitIndex) || (!isValid && entryIndex < sizeOfCalendar))
	{
		row = calendarEntryList ->at(entryIndex);
		printCalendarEntry(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}

	printCalendarFooter();
}

void UI::resultListDisplay(vector<string>* resultList)
{	
	assert(resultList!=NULL);

	int resultSize = resultList->size();
	int entryIndex = getResultInitIndex();
	int rowPosition = OPERATION_RESULT_Y;
	bool isValid = true;
	int nextInitIndex = getNextResultInitIndex(isValid);
	string row;

	if(resultSize>0)
	{
		clearBox(COMMAND_INIT_Y+5,1);
		highlightTitle(resultSize);
	}

	gotoxy(OPERATION_RESULT_X, OPERATION_RESULT_Y);
	
	while ((isValid && entryIndex < nextInitIndex) || (!isValid && entryIndex < resultSize ))
	{
		row = resultList ->at(entryIndex);
		printResultEntry(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}

	printResultFooter();
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

	setInitialIndexArrays(calendarEntryList, generalEntryList, resultList);
	if(resultList->size() !=0 )
		focusedField = SEARCH_RESULT;
	indexCurResultInitArray = 0;

	generalEntryListDisplay(generalEntryList);
	calendarEntryListDisplay(calendarEntryList);
	initializeDidUKnowStatus();
	diduknowHintDisplay();
	resultListDisplay(resultList);

	diduknowPrevStatus = CLEAR;
	drawCommandBox();
}

UI::UI(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{
	input = "";

	initializeDisplayModes();
	initializeInitArrayIndices();
	initializeDidUKnowStatus();
	initializeFocusedField();

	startingScreenDisplay();
	mainScreenDisplay( calendarEntryList, generalEntryList, resultList);
}

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