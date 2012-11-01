#include <cassert>

#include "UI.h"

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
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	cout<<"command:                                                                                                                ";
	cout<<endl;
	gotoxy(8,commandInitY);
}

void UI::setBackground()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void UI::clearBox(int startH, int height)
{
	setBackground();
	gotoxy(0,startH);
	for (int i=0; i<height; i++)
		for (int j=0; j<windowsWidth; j++)
			cout<<" ";
	gotoxy(0,startH);
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(startX,startY);

	cout<<words<<endl;
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

void UI::displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	assert(diduknowBoxList!=NULL);
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
		clearBox(diduknowInitY, bottomBoxHeight);
		diduknowBoxListDisplay(diduknowBoxList, generalEntryList->size());
		drawCommandBox();
		break;
	default:
		assert (false);
	}
}

void UI::changeFocusedField(vector<string>* diduknowBoxList)
{
	int sizeOfDiduknow = diduknowBoxList->size();

	switch (focusedField)
	{
	case GENERAL:
		focusedField = CALENDAR;
		break;
	case CALENDAR:
		if (sizeOfDiduknow !=0)
		{
			focusedField = DIDUKNOW;
		}
		else
		{
			focusedField = GENERAL;
		}
		break;
	case DIDUKNOW:
		focusedField = GENERAL;
		break;
	default:
		assert(false);
	}
}

void UI::scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	assert(diduknowBoxList!=NULL);
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
			drawCommandBox();
		}
		else if (generalInitRowIndex > 0)
		{
			generalInitRowIndex = 0;
			clearBox(generalInitY, generalBoxHeight +1);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}

		break;
	case CALENDAR:
		if (calendarInitRowIndex > calendarBoxHeight)
		{
			calendarInitRowIndex -= calendarBoxHeight;
			clearBox(calendarInitY, calendarBoxHeight);
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		else if (calendarInitRowIndex > 0)
		{
			calendarInitRowIndex = 0;
			clearBox(calendarInitY, calendarBoxHeight);
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex > 0)
		{
			diduknowInitRowIndex --;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList, generalEntryList->size());
			drawCommandBox();
		}
		break;
	default:
		assert (false);
	}
}

void UI::scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	assert(diduknowBoxList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	int generalSize = generalEntryList->size();
	int calendarSize = calendarEntryList->size();
	int diduknowSize = diduknowBoxList->size();

	switch (focusedField)
	{
	case GENERAL:
		if (generalInitRowIndex < generalSize -1 - generalBoxHeight)
		{
			generalInitRowIndex += generalBoxHeight;
			clearBox(generalInitY, generalBoxHeight +1);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}
		break;
	case CALENDAR:
		if (calendarInitRowIndex < calendarSize -1 - calendarBoxHeight)
		{
			calendarInitRowIndex += calendarBoxHeight;
			clearBox(calendarInitY, calendarBoxHeight);
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex < diduknowSize -1)
		{
			diduknowInitRowIndex ++;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList, generalSize);
			drawCommandBox();
		}
		break;
	default:
		assert (false);
	}
}

void UI::traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	assert(diduknowBoxList!=NULL);
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);

	char keyIn;
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
				scrollUp(calendarEntryList, generalEntryList, diduknowBoxList);
				break;
			case 80:
				scrollDown(calendarEntryList, generalEntryList, diduknowBoxList);
				break;
			case 73:
				changeDisplayMode();
				displayNewMode(calendarEntryList, generalEntryList, diduknowBoxList);
				break;
			}
			break;
		case TAB:
			changeFocusedField(diduknowBoxList);
			break;
		case BACKSPACE:
			if (input.size()>0)
			{
				input = input.substr(0, input.size()-1);
				cout << "\b \b";
			}
			break;
		default:
			if (keyIn != ENTER && input.size() < maxInputSize)
			{
				cout << keyIn;
				input += keyIn;
			}
			break;
		}
	}
}

void UI::displayCalendarString(int index, string row, int& rowPosition)
{
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[6] = {calendarIndexInitX, calendarDescriptionInitX, calendarLocationInitX,
							calendarTimeInitX, calendarDateInitX, calendarPriorityInitX};
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
				if (countPart == 1 && part.size() > maxCharDetailCalendar)
				{
					cout <<part.substr(0, maxCharDetailCalendar);
					gotoxy(locationArray[countPart], rowPosition + 1);
					cout <<part.substr(maxCharDetailCalendar, part.size());
					isOverflow = true;
				}
				else if (countPart == 2 && part.size() > maxCharLocationCalendar)
				{
					cout <<part.substr(0, maxCharLocationCalendar);
					gotoxy(locationArray[countPart], rowPosition + 1);
					cout <<part.substr(maxCharLocationCalendar, part.size());
					isOverflow = true;
				}
				else
				{
					cout << part;
				}

				break;
			case DISPLAY_PART:
				if (countPart == 1 && part.size() > maxCharDetailCalendar -3)
				{
					cout <<part.substr(0, maxCharDetailCalendar -3) << "...";
				}
				else if (countPart == 2 && part.size() > maxCharLocationCalendar - 3)
				{
					cout <<part.substr(0, maxCharLocationCalendar -3) << "...";
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

void UI::displayGeneralString(int index, string row, int &rowPosition)
{	
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

void UI::displayDiduknowString(int index, string row, int &rowPosition, int sizeOfGeneral)
{
	if (isGeneral(row))
	{
		displayGeneralString(index, row, rowPosition);
	}
	else
	{
		displayCalendarString(index + sizeOfGeneral, row, rowPosition);
	}
}

bool UI::isGeneral(string row)
{
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

void UI::coloredDisplayFormattedString(int index, string row, int rowIndex)
{	
	assert(index!=NULL);
	assert(row!="");
	assert(rowIndex!=NULL);

	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[6] = {calendarIndexInitX, calendarDescriptionInitX, calendarLocationInitX,
							calendarTimeInitX, calendarDateInitX, calendarPriorityInitX};
	int countPart = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countPart]);

	if (row[0] == '#' && row[1] == '#')		//for search result, the index of result in the entry list is added to result string,
	{										//so don't need to display index in the diduknowBoxList
		gotoxy(locationArray[countPart], rowIndex);
		cout<<index<<". ";
	}

	for (int i = 1; i<row.size(); i++)
	{
		if (row[i] != '#' )
		{
			part += row[i];
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countPart]);
			gotoxy(locationArray[countPart], rowIndex);
			countPart++;

			if (countPart != 2 || part.size() <= maxCharDetailCalendar - 3)
			{
				cout <<  part;
			}
			else
			{
				cout <<part.substr(0, maxCharDetailCalendar - 3) << "...";
			}
			part = "";
		}
		
	}
	cout<<endl;
	
}

void UI::generalEntryListDisplay(vector<string>* generalEntryList)
{	
	assert(generalEntryList!=NULL);

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
		displayGeneralString(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}
}

void UI::calendarEntryListDisplay(vector<string>* calendarEntryList)
{
	assert(calendarEntryList!=NULL);

	int sizeOfCalendar;
	int entryIndex;
	int rowPosition;
	string row;

	gotoxy(calendarInitX, calendarInitY);
	sizeOfCalendar=calendarEntryList->size();
	entryIndex = calendarInitRowIndex;
	rowPosition = calendarInitY;

	while (rowPosition < commandInitY && entryIndex <sizeOfCalendar)
	{
		row = calendarEntryList ->at(entryIndex);
		displayCalendarString(entryIndex + 1, row, rowPosition);
		entryIndex ++;
		rowPosition ++;
	}
}

void UI::diduknowBoxListDisplay(vector<string>* diduknowBoxList, int sizeOfGeneral)
{	
	assert(diduknowBoxList!=NULL);

	int sizeOfDiduknow;
	int entryIndex;
	int rowPosition;
	string row;

	gotoxy(calendarInitX, calendarInitY);
	sizeOfDiduknow=diduknowBoxList->size();
	entryIndex = diduknowInitRowIndex;
	rowPosition = diduknowInitY;

	while (rowPosition < windowsHeight -1 && entryIndex <sizeOfDiduknow)
	{
		row = diduknowBoxList ->at(entryIndex);
		displayDiduknowString(entryIndex + 1, row, rowPosition, sizeOfGeneral);
		entryIndex ++;
		rowPosition ++;
	}
}

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

void UI::mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(diduknowBoxList!=NULL);
	setBackground();
	system("CLS");

	writeTitle("General: ", 1,0);
	writeTitle("Calendar: ", 1, calendarInitY -2);

	generalEntryListDisplay(generalEntryList);
	calendarEntryListDisplay(calendarEntryList);
	diduknowBoxListDisplay(diduknowBoxList, generalEntryList->size());
	
	drawCommandBox();
}

UI::UI()
{
	input = "";
	focusedField = GENERAL;

	startingScreenDisplay();
}

void UI::userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(diduknowBoxList!=NULL);

	int generalTemp = generalEntryList->size() - generalBoxHeight;
	int calendarTemp = calendarEntryList->size() - calendarBoxHeight;
	int diduknowTemp = diduknowBoxList->size() - bottomBoxHeight;
	generalInitRowIndex = max(0, generalTemp);
	calendarInitRowIndex = max(0, calendarTemp);
	diduknowInitRowIndex = max(0, diduknowTemp);
	displayMode = DISPLAY_ALL;

	mainScreenDisplay(calendarEntryList, generalEntryList, diduknowBoxList);
	traceInput(calendarEntryList, generalEntryList, diduknowBoxList);
}

string UI::retrieveInput()
{
	return input;
}

Signal UI::retrieveFocusedField()
{
	return focusedField;
}

UI::~UI()
{
}