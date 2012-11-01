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
	cout<<"                                                                                                    ";
	cout<<"                          ____  ____                _____                                           ";
	cout<<"                          \\  \\\\/  //                |   \\\\                                          ";
	cout<<"                           \\  \\\" //                 |    \\\\                                         ";
	cout<<"                            \\   // ____  __ __  ____| |\\ || ____ __  ___                            ";
	cout<<"                             | || /   \\\\| || ||| _//| |/ ||/   ||\\ \\/ //                            ";
	cout<<"                             | || | O ||| |/ ||| || |    //| o || \\  //                             ";
	cout<<"                             |_|| \\___// \\__// |_|| |___// \\___|| /_//                              ";
	cout<<"                                                                                                    ";
	cout<<"                                                                                                    ";

}

void UI::drawCommandBox()
{
	gotoxy(0,commandInitY);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	cout<<"command:                                                                                            ";
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

void UI::clearCalendarBox()
{
	setBackground();
	gotoxy(0, calendarInitY);
	cout << "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                " << endl;
	gotoxy(0,calendarInitY);
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
		diduknowBoxListDisplay(diduknowBoxList);
		drawCommandBox();
		break;
	default:
		assert (false);
	}
}

void UI::changeFocusedField()
{
	switch (focusedField)
	{
	case GENERAL:
		focusedField = CALENDAR;
		break;
	case CALENDAR:
		focusedField = DIDUKNOW;
		break;
	case DIDUKNOW:
		focusedField = GENERAL;
		break;
	default:
		assert(true, false);
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
		if (generalInitRowIndex > 0)
		{
			generalInitRowIndex --;
			clearBox(generalInitY, generalBoxHeight);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}
		break;
	case CALENDAR:
		if (calendarInitRowIndex > 0)
		{
			calendarInitRowIndex --;
//			clearBox(calendarInitY, calendarBoxHeight);
			clearCalendarBox();
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex > 0)
		{
			diduknowInitRowIndex --;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList);
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
		if (generalInitRowIndex < generalSize -1)
		{
			generalInitRowIndex ++;
			clearBox(generalInitY, generalBoxHeight);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}
		break;
	case CALENDAR:
		if (calendarInitRowIndex < calendarSize -1)
		{
			calendarInitRowIndex ++;
//			clearBox(calendarInitY, calendarBoxHeight);
			clearCalendarBox();
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex < diduknowSize -1)
		{
			diduknowInitRowIndex ++;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList);
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
			changeFocusedField();
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
					cout <<part.substr(maxCharDetailCalendar + 1, part.size()-1);
					isOverflow = true;
				}
				else if (countPart == 2 && part.size() > maxCharLocationCalendar)
				{
					cout <<part.substr(0, maxCharLocationCalendar);
					gotoxy(locationArray[countPart], rowPosition + 1);
					cout <<part.substr(maxCharLocationCalendar + 1, part.size()-1);
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

void UI::displayGeneralString(/*int index, string row, int rowPosition*/)
{/*
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int locationArray[6] = {calendarIndexInitX, calendarDescriptionInitX, calendarLocationInitX,
							calendarTimeInitX, calendarDateInitX, calendarPriorityInitX};
	int countPart = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countPart]);

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
			countPart++;

			if ((countPart == 1 && maxCharDetailCalendar) || (countPart == 2 && maxCharLocation))
			{
				cout <<part.substr(0, maxCharDetail) << "...";
			}
			else
			{
				cout << part;
			}
			part = "";
		}
		
	}
	cout<<endl;*/
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
	int terminateIndex;
	int countRow = 0;
	string row;

	gotoxy(generalInitX, generalInitY);
	sizeOfGeneral=generalEntryList->size();
	
	terminateIndex = min (sizeOfGeneral, generalInitRowIndex + generalBoxHeight);
	
	for (int i = generalInitRowIndex; i< terminateIndex; i++)
	{
		row = generalEntryList ->at(i);
		coloredDisplayFormattedString(i+1, row, generalInitY + countRow);
		countRow ++;
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

void UI::diduknowBoxListDisplay(vector<string>* diduknowBoxList)
{	
	assert(diduknowBoxList!=NULL);

	int sizeOfDiduknow;
	int terminateIndex;
	int countRow = 0;
	string row;

	gotoxy(diduknowInitX, diduknowInitY);
	sizeOfDiduknow=diduknowBoxList->size();
	terminateIndex = min(sizeOfDiduknow, diduknowInitRowIndex + bottomBoxHeight);
	
	for (int i = diduknowInitRowIndex; i< terminateIndex; i++)
	{
		row = diduknowBoxList ->at(i);
		coloredDisplayFormattedString(i+1, row, diduknowInitY + countRow);
		countRow++;
	}
}

void UI::startingScreenDisplay()
{
	system("CLS");
	
	setScreenSize();

	drawBanner();
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"----------------------------------------------------------------------------------------------------";
	cout<<"|                              YourDay - always making your day :)                                 |";
	cout<<"----------------------------------------------------------------------------------------------------";
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(40,18);
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
	diduknowBoxListDisplay(diduknowBoxList);
	
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