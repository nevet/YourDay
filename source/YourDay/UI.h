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

#define windowsHeight 50
#define windowsWidth 100
#define generalTitleHeight 2
#define generalBoxHeight 15
#define calendarTitleHeight 3
#define calendarBoxHeight (windowsHeight-generalTitleHeight-generalBoxHeight-calendarTitleHeight-commandBoxHeight-bottomBoxHeight) 
#define commandBoxHeight 1
#define bottomBoxHeight 7

#define generalInitY (generalTitleHeight)
#define generalInitX 0
#define calendarInitY (generalInitY + generalBoxHeight + calendarTitleHeight)
#define calendarInitX 0
#define commandInitY (calendarInitY + calendarBoxHeight)
#define commandInitX 0
#define diduknowInitY (calendarInitY + calendarBoxHeight + commandBoxHeight)
#define diduknowInitX 0

//INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR
#define calendarIndexInitX 2
#define calendarDescriptionInitX 5
#define calendarLocationInitX (calendarTimeInitX - 10)
#define calendarTimeInitX 65
#define calendarDateInitX 80
#define calendarPriorityInitX 95

#define generalIndexInitX 2
#define generalDescriptionInitX 5
#define generalLocationInitX (generalTimeInitX- 10)
#define generalTimeInitX 95
#define generalDateInitX 95
#define generalPriorityInitX 95

#define maxCharLocationCalendar (calendarTimeInitX - calendarLocationInitX -1)
#define maxCharDetailCalendar (calendarLocationInitX - calendarDescriptionInitX -1)
#define maxCharLocationGeneral (generalTimeInitX - generalLocationInitX -1)
#define maxCharDetailGeneral (generalLocationInitX - generalDescriptionInitX -1)

#define maxCharDetail 12

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED

#define TAB 9
#define ENTER 13
#define BACKSPACE 8

#define maxInputSize 150

using namespace std;

class UI
{
private:

	HANDLE hConsole;
	string input;
	Signal focusedField;
	Signal displayMode;
	int generalInitRowIndex;
	int calendarInitRowIndex;
	int diduknowInitRowIndex;

	void setScreenSize();
	void setBackground();
	void drawBanner();
	void drawCommandBox();
	void clearBox(int startH, int height);
	void gotoxy(int x, int y);
	void writeTitle(string words, int startH, int startW);

	void clearCalendarBox();

	void changeDisplayMode();
	void displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void changeFocusedField();
	void scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);

	void displayCalendarString(int index, string row, int &rowPosition);
	void displayGeneralString(int index, string row, int &rowPosition);
	void coloredDisplayFormattedString(int,string, int);

	void generalEntryListDisplay(vector<string>* generalEntryList);
	void calendarEntryListDisplay(vector<string>* calendarEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList);
	void startingScreenDisplay();
	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
public:
	UI();

	void userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	string retrieveInput();
	Signal retrieveFocusedField();

	~UI();
};

#endif;