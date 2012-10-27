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

	//These are successful display message and will be used in intepreteSignal operation to get the feedback message string
	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	HANDLE hConsole;
	char displayBoard[boardHeight][boardWidth];

	void drawBanner();
	void writeWords(string words, int startH, int startW);
	void setNormal();
	void drawBox();
	void didUKnowBox();
	void setScreenSize();
	void gotoxy(int x, int y);

	string interpreteSignal(Signal outSignal);
	void coloredDisplayFormattedString(int,string);
	void displayEntryList( vector<string>* entryList, int entryListInitX, int entryListInitY);
	void startingScreenDisplay();	

public:
	UI(vector<string>* calendarEntryList, vector<string>* generalEntryList);

	string getInput();

	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList);
	void diduknowBoxListDisplay(string diduknowString);
	void diduknowBoxListDisplay(Signal diduknowSignal);

	~UI();
};

#endif