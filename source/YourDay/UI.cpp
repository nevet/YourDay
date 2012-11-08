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
    coord.X = windowsWidth; 
    coord.Y = windowsHeight; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = windowsHeight - 1; 
    Rect.Right = windowsWidth - 1; 

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
	gotoxy(0,commandInitY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4|FOREGROUND_INTENSITY);
	cout<<"command:";
	setBackground();
	cout<<"                                                                                                                ";
	cout<<"                                                                                                                        ";
	gotoxy(8,commandInitY);
}

void UI::gotoCommandBox()
{
	gotoxy(8,commandInitY);
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
		cout<<"                                                                                                                        ";
	
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
	gotoxy(8+currentChar,commandInitY);
	setBackground();
}

void UI::writeHighlightedTitle(string words,int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1|BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
	gotoxy(startX,startY);

	cout<<words<<endl;
	gotoxy(8+currentChar,commandInitY);
	setBackground();
}

void UI::highlightTitle(int searchBoxSize)
{
	switch (focusedField)
	{
	case GENERAL:
		writeHighlightedTitle("General: ", 1,0);
		writeTitle("Calendar: ", 1, calendarInitY -2);	
		if (searchBoxSize != 0)
		writeTitle("SearchBox: ", 0, commandInitY+5);
		break;
	case CALENDAR:
		writeTitle("General: ", 1,0);
		writeHighlightedTitle("Calendar: ", 1, calendarInitY -2);	
		if (searchBoxSize != 0)
		writeTitle("SearchBox: ", 0, commandInitY+5);
		break;
	case DIDUKNOW:
		writeTitle("General: ", 1,0);
		writeTitle("Calendar: ", 1, calendarInitY -2);	
		if (searchBoxSize != 0)
		writeHighlightedTitle("SearchBox: ", 0, commandInitY+5);
		break;
	}
}

void UI::changeDisplayMode()
{
	if (displayMode == DISPLAY_ALL)
	{
		displayMode = DISPLAY_PART;
	}
	else
	{
		displayMode = DISPLAY_ALL;
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
		clearBox(generalInitY, generalBoxHeight);
		generalEntryListDisplay(generalEntryList);
		drawCommandBox();
		break;
	case CALENDAR:
		clearBox(calendarInitY, calendarBoxHeight);
		calendarEntryListDisplay(calendarEntryList);
		drawCommandBox();
		break;
	case DIDUKNOW:
		clearBox(operationResultY, resultBoxHeight);
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
			focusedField = CALENDAR;
		}
		break;
	case DIDUKNOW:
		focusedField = GENERAL;
		clearBox(diduknowInitY,didUKnowHeight+2);
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
		if (generalInitRowIndex > generalBoxHeight)
		{
			generalInitRowIndex -= generalBoxHeight;
			clearBox(generalInitY, generalBoxHeight +1);
			generalEntryListDisplay(generalEntryList);
		}
		else if (generalInitRowIndex > 0)
		{
			generalInitRowIndex = 0;
			clearBox(generalInitY, generalBoxHeight +1);
			generalEntryListDisplay(generalEntryList);
		}
		
		break;
	case CALENDAR:
		if (calendarInitRowIndex > calendarBoxHeight)
		{
			calendarInitRowIndex -= calendarBoxHeight;
			clearBox(calendarInitY, calendarBoxHeight +1 );
			calendarEntryListDisplay(calendarEntryList);
		}
		else if (calendarInitRowIndex > 0)
		{
			calendarInitRowIndex = 0;
			clearBox(calendarInitY, calendarBoxHeight +1);
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex > resultBoxHeight)
		{
			diduknowInitRowIndex -= resultBoxHeight;
			clearBox(operationResultY, resultBoxHeight);
			resultListDisplay(resultList, generalEntryList->size());
		}
		else if (diduknowInitRowIndex > 0)
		{
			diduknowInitRowIndex = 0;
			clearBox(operationResultY, resultBoxHeight);
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
			clearBox(generalInitY, generalBoxHeight +1);
			generalEntryListDisplay(generalEntryList);
		}
		break;
	case CALENDAR:
		if (calendarEndRowIndex != calendarSize -1)
		{
			calendarInitRowIndex = calendarEndRowIndex +1;
			clearBox(calendarInitY, calendarBoxHeight + 1);
			calendarEntryListDisplay(calendarEntryList);
		}
		break;
	case DIDUKNOW:
		if (diduknowEndRowIndex != diduknowSize -1)
		{
			diduknowInitRowIndex = diduknowEndRowIndex +1;
			clearBox(operationResultY, resultBoxHeight);
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
				gotoxy(currentChar+8,commandInitY);
				break;
			case 80:
				scrollDown(calendarEntryList, generalEntryList, resultList);
				gotoxy(currentChar+8,commandInitY);
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
			if (keyIn != ENTER && input.size() < maxInputSize)
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
	diduknowStatus = DIDUKNOW_INIT;
}

void UI::initializeGeneralInitRowIndex(int generalSize)
{
	generalInitRowIndex = 0;
}

void UI::initializeCalendarInitRowIndex(int calendarSize)
{
/*	if (calendarSize % calendarBoxHeight)
	{
		calendarInitRowIndex = calendarBoxHeight * (calendarSize / calendarBoxHeight);
	}
	else
	{
		calendarInitRowIndex = calendarBoxHeight * (calendarSize / calendarBoxHeight -1);
	}
*/
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

bool UI::isPartEnoughSpace(int strLength, int maxLength, int spaceLeft)
{
	int numberOfRow;

	if (strLength % maxLength == 0)
	{
		numberOfRow = strLength / maxLength;
	}
	else 
	{
		numberOfRow = strLength / maxLength +1;
	}

	return (numberOfRow <= spaceLeft);
}

void UI::printPart(string part, int maxLength, int initX, int initY, int &endY)
{
/*	int curY = initY;
	int curX = initX;

	string word;
	istringstream str(part);
	
	while (str >> word)
	{
		gotoxy(curX, curY);
		if (curX + word.length() <= maxLength)	
		{
			cout << word;
			curX += word.length();

			if (curX != maxLength)
			{
				cout <<" ";
				curX ++;
			}
		}
		else
		{
			curY ++;
		}
	}
*/
	int initIndex = 0;

	for (int i = 0; i < part.length() / maxLength; i++) 
	{
		gotoxy(initX, initY);
		cout << part.substr(initIndex, maxLength);
		initIndex += maxLength;
		initY++;
	}

	if (part.length() % maxLength != 0)
	{
		gotoxy(initX, initY);
		cout << part.substr(initIndex, part.length() % maxLength);
		initY ++;
	}

	endY = initY -1;
}

bool UI::isCalendarEntryEnoughSpace(string description, string location, int rowPosition)
{
	bool ans = false;

	if ((isPartEnoughSpace (description.length(), maxCharDetailCalendar, calendarInitY + calendarBoxHeight - rowPosition))
		&& (isPartEnoughSpace (location.length(), maxCharLocationCalendar, calendarInitY + calendarBoxHeight - rowPosition)))
		ans = true;

	return ans;
}

void UI::printCalendarString(int index, string row, int& rowPosition, bool& isPrinted)
{
	assert(row!= "");
	assert(rowPosition >= 0 && rowPosition <= windowsHeight);

	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[6] = {calendarIndexInitX, calendarDescriptionInitX, calendarLocationInitX,
							calendarTimeInitX, calendarDateInitX, calendarPriorityInitX};
	string partArray[6];
	int endDetailPosition = rowPosition;
	int endLocationPosition = rowPosition;

	extractParts(row, partArray);
	string description = partArray[1];
	string location = partArray[2];
	
	switch (displayMode)
	{
	case DISPLAY_ALL:
		if (isCalendarEntryEnoughSpace(description, location, rowPosition))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[0]);
			clearBox(rowPosition,1);	
			gotoxy(locationArray[0], rowPosition);
			cout<<index<<". ";

			gotoxy(locationArray[1],rowPosition);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[1]);
			printPart(partArray[1], maxCharDetailCalendar, locationArray[1], rowPosition, endDetailPosition);

			gotoxy(locationArray[2],rowPosition);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[2]);
			printPart(partArray[2], maxCharLocationCalendar, locationArray[2], rowPosition, endLocationPosition);
			isPrinted = true;

			for (int i = 3; i<6; i++)
			{
				gotoxy(locationArray[i],rowPosition);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[i]);
				cout << partArray[i];
			}
		}
		else
		{
			isPrinted = false;
		}

		break;
	case DISPLAY_PART:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[0]);
		clearBox(rowPosition,1);
		gotoxy(locationArray[0], rowPosition);
		cout<<index<<". ";

		for (int i = 1; i<6; i++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[i]);
			gotoxy(locationArray[i], rowPosition);

				if (i == 1 && partArray[i].size() > maxCharDetailCalendar -3)
				{
					printf("%s...", partArray[i].substr(0, maxCharDetailCalendar -3).c_str());
				}
				else if (i == 2 && partArray[i].size() > maxCharLocationCalendar - 3)
				{
					printf("%s...",partArray[i].substr(0, maxCharLocationCalendar -3).c_str());
				}
				else
				{
					printf("%s",partArray[i].c_str());
				}
		}
		isPrinted = true;
		break;
	}

	rowPosition = max(endDetailPosition, endLocationPosition);
	cout<<endl;
}

void UI::printGeneralString(int index, string row, int &rowPosition)
{	
	assert(row!= "");
	assert(rowPosition >= 0 && rowPosition <= windowsHeight);
	
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[6] = {generalIndexInitX, generalDescriptionInitX, generalLocationInitX,
							generalTimeInitX, generalDateInitX, generalPriorityInitX};
	int countPart = 0;
	bool isOverflow = false;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countPart]);

	gotoxy(locationArray[countPart], rowPosition);
	cout<<index<<". ";

	for (int i = 1; i<row.size(); i++)
	{
		if (row[i] != '#' )
		{
			part += row[i];
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countPart]);
			gotoxy(locationArray[countPart], rowPosition);

			switch (displayMode)
			{
			case DISPLAY_ALL:
				if (countPart == 1 && part.size() > maxCharDetailGeneral)
				{
					cout <<part.substr(0, maxCharDetailGeneral);
					gotoxy(locationArray[countPart], rowPosition + 1);
					cout <<part.substr(maxCharDetailGeneral, part.size());
					isOverflow = true;
				}
				else if (countPart == 2 && part.size() > maxCharLocationGeneral)
				{
					cout <<part.substr(0, maxCharLocationGeneral);
					gotoxy(locationArray[countPart], rowPosition + 1);
					cout <<part.substr(maxCharLocationGeneral, part.size());
					isOverflow = true;
				}
				else
				{
					cout << part;
				}

				break;
			case DISPLAY_PART:
				if (countPart == 1 && part.size() > maxCharDetailGeneral -3)
				{
					cout <<part.substr(0, maxCharDetailGeneral -3) << "...";
				}
				else if (countPart == 2 && part.size() > maxCharLocationGeneral - 3)
				{
					cout <<part.substr(0, maxCharLocationGeneral -3) << "...";
				}
				else
				{
					cout << part;
				}
				break;
			}
			countPart ++;
			part = "";
		}
		
	}
	if (isOverflow)
	{
		rowPosition ++;
	}

	cout<<endl;
}

void UI::printResultString(int index, string row, int &rowPosition, int sizeOfGeneral)
{
	assert(row!= "");
	assert(rowPosition >= 0 && rowPosition <= windowsHeight);
	if (isGeneral(row))
	{
		printGeneralString(index, row, rowPosition);
	}
	else
	{
//		printCalendarString(index + sizeOfGeneral, row, rowPosition, isPrinted);
	}
}

//@author A0088455R
void UI::printDiduknowHints()
{
	clearBox(diduknowInitY,didUKnowHeight+2);
	gotoxy(diduknowInitX, diduknowInitY);
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

	gotoxy(generalInitX, generalInitY);
	sizeOfGeneral=generalEntryList->size();
	entryIndex = generalInitRowIndex;
	rowPosition = generalInitY;
	
	while (rowPosition < (calendarInitY - calendarTitleHeight) && entryIndex <sizeOfGeneral)
	{
		row = generalEntryList ->at(entryIndex);
		printGeneralString(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}

	generalEndRowIndex = entryIndex -1;
	if (generalEndRowIndex != sizeOfGeneral -1)
	{
		printContinueFooter();
	}
}

void UI::calendarEntryListDisplay(vector<string>* calendarEntryList)
{

	int sizeOfCalendar;
	int entryIndex;
	int rowPosition;
	string row;
	bool isLastLineHaveSpace = true;

	gotoxy(calendarInitX, calendarInitY);
	sizeOfCalendar=calendarEntryList->size();
	entryIndex = calendarInitRowIndex;
	rowPosition = calendarInitY;

	while (rowPosition < calendarInitY + calendarBoxHeight && entryIndex <sizeOfCalendar && isLastLineHaveSpace)
	{
		row = calendarEntryList ->at(entryIndex);
		printCalendarString(entryIndex + 1, row, rowPosition, isLastLineHaveSpace);
		if (isLastLineHaveSpace)
		{
			entryIndex ++;
			rowPosition ++;
		}
	}

	calendarEndRowIndex = entryIndex -1;
	if (calendarEndRowIndex != sizeOfCalendar -1)
	{
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
	
	gotoxy(operationResultX, diduknowInitY+1);
	sizeOfDiduknow=resultList->size();
	entryIndex = diduknowInitRowIndex;
	
	if(resultList->size()>0)
	{
		clearBox(commandInitY+2,1);
		highlightTitle(resultList->size());
	}

	gotoxy(1,commandInitY+3);
	rowPosition = commandInitY+3;
	while (rowPosition < windowsHeight-1 && entryIndex <sizeOfDiduknow)
	{
		row = resultList ->at(entryIndex);
		printResultString(entryIndex + 1, row, rowPosition, sizeOfGeneral);
		entryIndex ++;
		rowPosition ++;
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
	gotoxy(8+currentChar,commandInitY);
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

	displayMode = DISPLAY_ALL;
	focusedField = GENERAL;	
	diduknowPrevStatus=DIDUKNOW_CLEAR;

	startingScreenDisplay();
}

void UI::userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList)
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(resultList!=NULL);

	mainScreenDisplay(calendarEntryList, generalEntryList, resultList);
	traceInput(calendarEntryList, generalEntryList, resultList);
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
	clearBox(diduknowInitY,bottomBoxHeight);
	gotoxy(0,diduknowInitY);
	setBackground();
	cout << message <<endl;
	drawCommandBox();
	getchar();
}

UI::~UI()
{
}	 