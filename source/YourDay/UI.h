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

#define windowsHeight 25
#define windowsWidth 80
#define generalTitleHeight 2
#define generalBoxHeight 5
#define calendarTitleHeight 2
#define calendarBoxHeight (windowsHeight-generalTitleHeight-generalBoxHeight-calendarTitleHeight-commandBoxHeight-bottomBoxHeight)
#define commandBoxHeight 1
#define bottomBoxHeight 3

#define generalInitY (generalTitleHeight)
#define generalInitX 0
#define calendarInitY (generalInitY + generalBoxHeight + calendarTitleHeight)
#define calendarInitX 0
#define commandInitY (calendarInitY + calendarBoxHeight)
#define commandInitX 0
#define diduknowInitY (calendarInitY + calendarBoxHeight + commandBoxHeight)
#define diduknowInitX 0

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

using namespace std;

class UI
{
private:

	enum MainFields
	{
		GENERAL, CALENDAR, DIDUKNOW
	};

	HANDLE hConsole;
	string input;
	MainFields focusedField;
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

	void changeFocusedField();
	void scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	void traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);

	void coloredDisplayFormattedString(int,string);
	void generalEntryListDisplay(vector<string>* generalEntryList);
	void calendarEntryListDisplay(vector<string>* calendarEntryList);
	void diduknowBoxListDisplay(vector<string>* diduknowBoxList);
	void startingScreenDisplay();
	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
public:
	UI();

	void userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList);
	string retrieveInput();

	~UI();
};

#endif;