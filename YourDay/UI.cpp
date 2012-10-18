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
	SMALL_RECT windowSize = {5, 5,120, 50};

	COORD buffer={120,1500};
	SetConsoleScreenBufferSize(hconsole,buffer);
	SetConsoleWindowInfo(hconsole, TRUE, &windowSize);
}

void UI::setStatus(Signal statusSignal)
{
	status = statusSignal;
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
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	cout<<"                                    ____  ____                _____                                                 "<<endl;
	cout<<"                                    \\  \\\\/  //                |   \\\\                                                "<<endl;
	cout<<"                                     \\  \"  //                 |    \\\\                                               "<<endl;
	cout<<"                                      \\   // ____  __ __  ____| |\\ || ____ __  ___                                  "<<endl;
	cout<<"                                       | || /   \\\\| || ||| _//| |/ ||/   ||\\ \\/ //                                  "<<endl;
	cout<<"                                       | || | O ||| |/ ||| || |    //| o || \\  //                                   "<<endl;
	cout<<"                                       |_|| \\___// \\__// |_|| |___// \\___|| /_//                                    "<<endl;
	cout<<"                                                                                                                    "<<endl;
	//system("color 0F");
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"|                                    YourDay - always making your day :)                                           |"<<endl;
	cout<<"--------------------------------------------------------------------------------------------------------------------"<<endl;
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(50,30);
	cout<<"Press Enter to continue\n";
	setStatus(SUCCESS);
}

void UI::mainScreenDisplay()
{
	system("CLS");
	
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