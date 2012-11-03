#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <conio.h>
#include "Signal.h"

#define windowsHeight 40
#define windowsWidth 120
#define generalTitleHeight 2
#define generalBoxHeight 12
#define calendarTitleHeight 3
#define calendarBoxHeight (windowsHeight-generalTitleHeight-generalBoxHeight-calendarTitleHeight-commandBoxHeight -bottomBoxHeight -2) //14
														// -2 because don't use the line before command box and the end line of the console
#define commandBoxHeight 2
#define bottomBoxHeight 6 //don't use the last line of the console

#define generalInitY (generalTitleHeight)
#define generalInitX 0
#define calendarInitY (generalInitY + generalBoxHeight + calendarTitleHeight)
#define calendarInitX 0
#define commandInitY (calendarInitY + calendarBoxHeight +1)
#define commandInitX 0
#define diduknowInitY (commandInitY + commandBoxHeight)
#define diduknowInitX 0

//INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR
#define calendarIndexInitX 2
#define calendarDescriptionInitX 6
#define calendarLocationInitX (calendarTimeInitX - 20)
#define calendarTimeInitX 85
#define calendarDateInitX 99
#define calendarPriorityInitX 112

#define generalIndexInitX 2
#define generalDescriptionInitX 6
#define generalLocationInitX (generalTimeInitX- 10)
#define generalTimeInitX 113
#define generalDateInitX 113
#define generalPriorityInitX 113

#define maxCharLocationCalendar (calendarTimeInitX - calendarLocationInitX -1)
#define maxCharDetailCalendar (calendarLocationInitX - calendarDescriptionInitX -1)
#define maxCharLocationGeneral (generalTimeInitX - generalLocationInitX -1)
#define maxCharDetailGeneral (generalLocationInitX - generalDescriptionInitX -1)

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED

#define TAB 9
#define ENTER 13
#define BACKSPACE 8

#define maxInputSize 192

using namespace std;

class UI
{
private:

	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	HANDLE hConsole;
	string input;
	Signal focusedField;
	Signal displayMode;
	int generalInitRowIndex;
	int calendarInitRowIndex;
	int diduknowInitRowIndex;
	int generalEndRowIndex; // in case an entry occupies > 1 line, end index is not initial index + box height
	int calendarEndRowIndex;
	int diduknowEndRowIndex;

	string interpreteSignal(Signal status);

	void setScreenSize();
	void setBackground();
	void drawBanner();
	void drawCommandBox();
	void clearBox(int startH, int height);
	void gotoxy(int x, int y);
	void writeTitle(string words, int startH, int startW);

	void changeDisplayMode();
	void displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void changeFocusedField(vector<string>* diduknowBoxList);
	void scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);

	void displayCalendarString(int index, string row, int &rowPosition);
	void displayGeneralString(int index, string row, int &rowPosition);
	void displayDiduknowString(int index, string row, int &rowPosition, int sizeOfGeneral);
	bool isGeneral(string row);

	void generalEntryListDisplay(vector<string>* generalEntryList);
	void calendarEntryListDisplay(vector<string>* calendarEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList, int sizeOfGeneral);
	void startingScreenDisplay();
	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
public:
	UI();

	void userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	string retrieveInput();
	Signal retrieveFocusedField();
	void displayMessage(string message);
	void displayStatus(Signal status);

	~UI();
};

#endif;