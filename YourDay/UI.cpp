/**
* UI class is a part of UI part and will be called in the UIHandler
* UI class is used to display User Interface to the screen
* UI class has 2 main APIs to do this functionality:
* startingScreenDisplay():void to diisplay starting screen to user at the beginning of the program
* mainScreenDisplay():void to display main screen to interact with user
*/




#include "UI.h"


void UI::setScreenSize()
{
	HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	//SMALL_RECT windowSize = {5, 5,windowsHeight, windowsWidth};

	COORD buffer={0,0};
	SetConsoleScreenBufferSize(hconsole,buffer);
//	SetConsoleWindowInfo(hconsole, TRUE, &windowSize);
}

void UI::drawBanner()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	cout<<"                ____  ____                _____                                 ";
	cout<<"                \\  \\\\/  //                |   \\\\                                ";
	cout<<"                 \\  \\\" //                 |    \\\\                               ";
	cout<<"                  \\   // ____  __ __  ____| |\\ || ____ __  ___                  ";
	cout<<"                   | || /   \\\\| || ||| _//| |/ ||/   ||\\ \\/ //                  ";
	cout<<"                   | || | O ||| |/ ||| || |    //| o || \\  //                   ";
	cout<<"                   |_|| \\___// \\__// |_|| |___// \\___|| /_//                    ";
	cout<<"                                                                                ";
}

void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void UI::writeWords(string words, int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(startX,startY);

	cout<<words<<endl;
}

UI::UI()
{
}

Signal UI::getStatus()
{
	return status;
}

void UI::clearStatus()
{
	status = CLEAR;
}

void UI::startingScreenDisplay()
{
	system("CLS");
	
	drawBanner();
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"--------------------------------------------------------------------------------";
	cout<<"|                    YourDay - always making your day :)                       |";
	cout<<"--------------------------------------------------------------------------------";
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(30,18);
	cout<<"Press Enter to continue";
	setStatus(SUCCESS);
	getchar();
}

void UI::drawBox()
{
	gotoxy(0,boardHeight);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	cout<<"command:                                                                        ";
	cout<<endl;
	gotoxy(8,boardHeight);
}

void UI::didUKnowBox()
{
	gotoxy(0,boardHeight+1);
	cout<<"                                                                                ";
	cout<<"                                                                                ";
	cout<<"                                                                               ";
	gotoxy(0,boardHeight+1);
}

void UI::setNormal()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void UI::mainScreenDisplay(vector<string>* calendarEntryList,vector<string>* generalEntryList)
{
	setNormal();
	system("CLS");
	
	writeWords("General",0,0);
	writeWords("Calendar",0,10);

	displayEntryList( calendarEntryList, generalEntryList );

	drawBox();
	setStatus(SUCCESS);
}

void UI :: gotoxy(int x, int y) //goes to x,y console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI :: displayEntryList(vector<string>* calendarEntryList, vector<string>* generalEntryList)
{
	int sizeOfCalendar;
	int sizeOfGeneral;
	string formatString;

	gotoxy(generalEntryListInitX, generalEntryListInitY);

	sizeOfGeneral=generalEntryList->size();

	for (int i=0; i< sizeOfGeneral; i++)
	{
		string row;
		row = generalEntryList->at(i) ;
		coloredDisplayFormattedString(i+1, row);
	}
	gotoxy(calendarEntryListInitX, calendarEntryListInitY);
	sizeOfCalendar=calendarEntryList->size();
	for (int i=0; i< sizeOfCalendar; i++)
	{
		string row;
		row = calendarEntryList->at(i) ;
		coloredDisplayFormattedString(i+sizeOfGeneral+1, row);
	}
}

void UI::coloredDisplayFormattedString(int index, string row)
{
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int countColor = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countColor]);
	cout<<" "<<index<<". ";
	
	for (int i = 1; i<row.size(); i++)
	{
		if (row[i] != '#' )
		{
			part += row[i];
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countColor]);
			countColor++;
			cout <<  part;
			part = "";
			if ((i !=row.size()-1)&&(i != 1))
			{
				cout << "\t";
			}
		}
		
	}
	cout<<endl;
	
}

UI::~UI()
{
}