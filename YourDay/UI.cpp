/**
* UI class is a part of UI part and will be called in the UIHandler
* UI class is used to display User Interface to the screen
* UI class has 2 main APIs to do this functionality:
* startingScreenDisplay():void to diisplay starting screen to user at the beginning of the program
* mainScreenDisplay():void to display main screen to interact with user
*/




#include "UI.h"

void UI::gobackBox()
{
	gotoxy(0,boardHeight);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}
void UI::setScreenSize()
{
	HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
	//SMALL_RECT windowSize = {5, 5,windowsHeight, windowsWidth};

	COORD buffer={0,0};
	SetConsoleScreenBufferSize(hconsole,buffer);
//	SetConsoleWindowInfo(hconsole, TRUE, &windowSize);
}

void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

void UI::writeWords(string words, int startH, int startW)
{
	int len = words.length();

	for (int i = 0; i < len; i++)
	{
		displayBoard[startH][startW + i] = words[i];
	}
}

UI::UI()
{
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			displayBoard[i][j] = ' ';

	writeWords("General", 0, 0);
	writeWords("Calendar", 10, 0);
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
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"--------------------------------------------------------------------------------";
	cout<<"|                    YourDay - always making your day :)                       |";
	cout<<"--------------------------------------------------------------------------------";
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(30,18);
	cout<<"Press Enter to continue";
	setStatus(SUCCESS);
}

void UI::drawBox()
{
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	for(int i=0;i<windowsWidth;i++)
		cout<<' ';
	cout<<endl;
	gotoxy(0,boardHeight);
}

void UI::setNormal()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void UI::mainScreenDisplay()
{
	system("CLS");

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
			cout<<displayBoard[i][j];
		}

	}

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

UI::~UI()
{
}