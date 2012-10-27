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

	//These are successful display message and will be used in intepreteSignal operation to get the feedback message string
	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	//These are error feedback messages on user input and will be used in intepreteSignal operation to get the feedback message string
	static const string COMMAND_ERROR_MESSAGE;
	static const string LENGTH_EXCEED_ERROR_MESSAGE;
	static const string LENGTH_ZERO_ERROR_MESSAGE;
	static const string INDEX_ERROR_MESSAGE;
	static const string INVALID_DATE_ERROR_MESSAGE;
	static const string INVALID_TIME_ERROR_MESSAGE;
	static const string UNDO_ERROR_MESSAGE;

	//These are error messages on displaying UI and will be used in intepreteSignal operation to get the feedback message string
	static const string DISPLAY_ERROR_MESSAGE;

	//These are error messages on executing commands and will be used in intepreteSignal operation to get the feedback message string
	static const string NULL_EXECUTOR_ERROR_MESSAGE;
	static const string ADD_FAILED_MESSAGE;
	static const string DELETE_FAILED_MESSAGE;
	static const string SEARCH_FAILED_MESSAGE;
	static const string UPDATE_FAILED_MESSAGE;

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
	void displayEntryList( vector<string>* calendarEntryList, vector<string> *generalEntryList );
	void startingScreenDisplay();	

public:
	UI(vector<string>* calendarEntryList, vector<string>* generalEntryList);

	string getInput();

	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList);
	void diduknowBoxListDisplay(string diduknowString);

	~UI();
};

#endif