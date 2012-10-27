#include "UI.h"

//Set output strings for successful feedback signals
const string UI::CLEAR_SIGNAL_MESSAGE = "Command done\n";
const string UI::ADD_SUCCESSFUL_MESSAGE = "Added successfully\n";
const string UI::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully\n";
const string UI::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully\n";

string UI::interpreteSignal(Signal outSignal)
{
	string outString;

	switch (outSignal)
	{
	case CLEAR:
		{
			outString = CLEAR_SIGNAL_MESSAGE;
			break;
		}
	case ADD_S:
		{
			outString = ADD_SUCCESSFUL_MESSAGE;
			break;
		}
	case  DELETE_S:
		{
			outString = DELETE_SUCCESSFUL_MESSAGE;
			break;
		}
	case  UPDATE_S:
		{
			outString = UPDATE_SUCCESSFUL_MESSAGE;
			break;
		}
	default:
		{
			outString = "";
			break;
		}
	}

	return outString;
}

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

void UI::writeWords(string words, int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(startX,startY);

	cout<<words<<endl;
}

UI::UI(vector<string>* calendarEntryList, vector<string>* generalEntryList)
{
	startingScreenDisplay();
	mainScreenDisplay(calendarEntryList,generalEntryList);
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

	displayEntryList( generalEntryList, generalEntryListInitX, generalEntryListInitY );
	displayEntryList( calendarEntryList, calendarEntryListInitX, calendarEntryListInitY );

	drawBox();
}

void UI :: gotoxy(int x, int y) //goes to x,y console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI :: displayEntryList(vector<string>* entryList, int entryListInitX, int entryListInitY)
{
	int sizeOfCalendar;
	int sizeOfGeneral;
	string formatString;

	gotoxy(entryListInitX, entryListInitY);

	sizeOfGeneral=entryList->size();

	for (int i=0; i< sizeOfGeneral; i++)
	{
		string row;
		row = entryList->at(i) ;
		coloredDisplayFormattedString(i+1, row);
	}
}

void UI::coloredDisplayFormattedString(int index, string row)
{
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int countColor = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countColor]);

	if (row[0] == '#' && row[1] == '#')		//for search result, the index of result in the entry list is added to result string,
	{										//so don't need to display index in the diduknowBoxList
		cout<<" "<<index<<". ";
	}

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

string UI::getInput()
{
	string input;
	getline(cin, input);
	return input;
}

void UI::diduknowBoxListDisplay(vector<string> *diduknowBoxList)
{
	setNormal();
	didUKnowBox();

	displayEntryList(diduknowBoxList, 0, boardHeight + 1);

	drawBox();
}

void UI::diduknowBoxListDisplay(string diduknowString)
{
	setNormal();
	didUKnowBox();

	cout << diduknowString;

	drawBox();
}

void UI::diduknowBoxListDisplay(Signal diduknowSignal)
{
	setNormal();
	didUKnowBox();

	string signalString = interpreteSignal (diduknowSignal);
	cout << signalString;

	drawBox();
}

UI::~UI()
{
}