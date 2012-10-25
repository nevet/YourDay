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
#define entryListInitX 0
#define entryListInitY 2

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
	void displayEntryList( vector<string> *entryList );
	void coloredDisplayFormattedString(string);
public:

	UI();
	void setNormal();
	void drawBox();
	void didUKnowBox();
	Signal getStatus();
	void setScreenSize();
	void clearStatus();
	void gotoxy(int x,int y);
	/**
	* This operation is used to display starting screen to the user at the beginning of the program
	* and will be called in UIHandler class
	*/
	void startingScreenDisplay();

	/**
	* This operation is used to display the main screen to interact with the user
	* and will be called in UIHandler class
	*/
	void mainScreenDisplay(vector<string>* entryList);

	~UI();
};

#endif