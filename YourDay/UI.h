/**
* UI class is a part of UI part and will be called in the UIHandler
* UI class is used to display User Interface to the screen
* UI class has 2 main APIs to do this functionality:
* startingScreenDisplay():void to diisplay starting screen to user at the beginning of the program
* mainScreenDisplay():void to display main screen to interact with user
*/
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "Signal.h"

#define windowsHeight 25
#define windowsWidth 80
#define bottomBoardHeight 3
#define boxHeight 1
#define boardHeight (windowsHeight - boxHeight - bottomBoardHeight)
#define boardWidth windowsWidth
#define boxWidth windowsWidth
#define generalEntryListInitX 0
#define generalEntryListInitY 2
#define calendarEntryListInitX 0
#define calendarEntryListInitY 12

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED

using namespace std;

class UI
{
private:
	Signal status;
	HANDLE hConsole;
	char displayBoard[boardHeight][boardWidth];

	void setStatus(Signal statusSignal);

	void drawBanner();
	void writeWords(string words, int startH, int startW);
	void setNormal();
	void drawBox();
	void didUKnowBox();
	void setScreenSize();
	void gotoxy(int x, int y);

	void coloredDisplayFormattedString(int,string);
	void displayEntryList( vector<string>* calendarEntryList, vector<string> *generalEntryList );
	void startingScreenDisplay();	

public:
	UI(vector<string>* calendarEntryList, vector<string>* generalEntryList);

	Signal getStatus();
	void clearStatus();
	
	string getInput();

	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList);
	void diduknowBoxListDisplay(string diduknowString);

	~UI();
};

#endif