/**
* UI class is a part of UI part and will be called in the UIHandler
* UI class is used to display User Interface to the screen
* UI class has 2 main APIs to do this functionality:
* startingScreenDisplay():void to diisplay starting screen to user at the beginning of the program
* mainScreenDisplay():void to display main screen to interact with user
*/




#include "UI.h"

//Set output strings for successful feedback signals
const string UI::CLEAR_SIGNAL_MESSAGE = "Command done\n";
const string UI::ADD_SUCCESSFUL_MESSAGE = "Added successfully\n";
const string UI::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully\n";
const string UI::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully\n";

//set output strings for error feedback signals on user input
const string UI::COMMAND_ERROR_MESSAGE = "Wrong command\n";
const string UI::LENGTH_EXCEED_ERROR_MESSAGE = "Command length exceeded the valid range\n";
const string UI::LENGTH_ZERO_ERROR_MESSAGE = "Cannot enter command with empty detail\n";
const string UI::INDEX_ERROR_MESSAGE = "Please enter an index\n";
const string UI::INVALID_DATE_ERROR_MESSAGE = "Invalid date\n";
const string UI::INVALID_TIME_ERROR_MESSAGE = "Invalid time\n";
const string UI::UNDO_ERROR_MESSAGE = "Nothing to undo\n";

//set output strings for error feedback signals on displaying UI
const string UI::DISPLAY_ERROR_MESSAGE = "Display error\n";

//set output strings for error feedback signals on executing commands
const string UI::NULL_EXECUTOR_ERROR_MESSAGE = "Executor pointer is NULL\n";
const string UI::ADD_FAILED_MESSAGE = "Add failed\n";
const string UI::DELETE_FAILED_MESSAGE = "Delete failed\n";
const string UI::SEARCH_FAILED_MESSAGE = "Cannot find the key word\n";
const string UI::UPDATE_FAILED_MESSAGE = "Update failed\n";

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
	case  COMMAND_E:
		{
			outString = COMMAND_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_X_E:
		{
			outString = LENGTH_EXCEED_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_Z_E:
		{
			outString = LENGTH_ZERO_ERROR_MESSAGE;
			break;
		}
	case  INDEX_E:
		{
			outString = INDEX_ERROR_MESSAGE;
			break;
		}
	case  DATE_E:
		{
			outString = INVALID_DATE_ERROR_MESSAGE;
			break;
		}
	case  TIME_E:
		{
			outString = INVALID_TIME_ERROR_MESSAGE;
			break;
		}
	case  DISPLAY_E:
		{
			outString = DISPLAY_ERROR_MESSAGE;
			break;
		}
	case  UNDO_E:
		{
			outString = UNDO_ERROR_MESSAGE;
			break;
		}
	case  EXENULL_E:
		{
			outString = NULL_EXECUTOR_ERROR_MESSAGE;
			break;
		}
	case  ADD_F:
		{
			outString = ADD_FAILED_MESSAGE;
			break;
		}
	case  DELETE_F:
		{
			outString = DELETE_FAILED_MESSAGE;
			break;
		}
	case  SEARCH_F:
		{
			outString = SEARCH_FAILED_MESSAGE;
			break;
		}
	case  UPDATE_F:
		{
			outString = UPDATE_FAILED_MESSAGE;
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

	displayEntryList( calendarEntryList, generalEntryList );

	drawBox();
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
	int size = diduknowBoxList ->size();
	setNormal();
	didUKnowBox();

	for (int i=0; i< size; i++)
	{
		string row;

		row = diduknowBoxList->at(i) ;
		coloredDisplayFormattedString(i+1,row);
	}

	drawBox();
}

void UI::diduknowBoxListDisplay(string diduknowString)
{
	setNormal();
	didUKnowBox();

	cout << diduknowString;

	drawBox();
}


UI::~UI()
{
}