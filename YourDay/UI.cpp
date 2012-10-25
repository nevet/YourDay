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
}

void UI::setNormal()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void UI::mainScreenDisplay(vector<string>* entryList)
{
	setNormal();
	system("CLS");
	
	writeWords("General",0,0);
	writeWords("Calendar",0,10);

	displayEntryList( entryList );

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

void UI :: displayEntryList(vector<string>* entryList)
{
	int size;
	string formatString;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_BLUE);

	gotoxy(entryListInitX,entryListInitY);
	
	size=entryList->size();

	for (int i=0; i< size; i++)
	{
		string row;
		row = entryList->at(i) ;
		formatString = decoder(row);
		cout<<"     "<<i+1<<"."<<formatString<<endl;
	}

}

string UI::decoder(string input)
{
	string decodedString = "";
	int size = input.size();
	char curChar;			//current character in input string
	

	for (int i = 0; i < input.size(); i++)
	{
		curChar = input[i];
		if (curChar != '#')
		{
			decodedString += curChar;
		}
		else
		{
			if (i != input.size()-1 && input[i+1] != '#' && decodedString != "")
			{
				decodedString += ": ";
			}
		}
	}

	return decodedString;
}

UI::~UI()
{
}