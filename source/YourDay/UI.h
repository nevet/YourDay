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

#define WINDOWS_HEIGHT 40
#define WINDOWS_WIDTH 120
#define GENERAL_TITLE_HEIGHT 2
#define GENERAL_BOX_HEIGHT 12
#define CALENDAR_TITLE_HEIGHT 3
#define CALENDAR_BOX_HEIGHT (WINDOWS_HEIGHT-GENERAL_TITLE_HEIGHT-GENERAL_BOX_HEIGHT-CALENDAR_TITLE_HEIGHT-COMMAND_BOX_HEIGHT-BOTTOM_BOX_HEIGHT -2) 
							// -2 because don't use the line before command box and the last line of the console
#define COMMAND_BOX_HEIGHT 2
#define BOTTOM_BOX_HEIGHT 6 //don't use the last line of the console
#define DIDUKNOW_HEIGHT 4
#define RESULT_BOX_HEIGHT (WINDOWS_HEIGHT - OPERATION_RESULT_Y )

#define GENERAL_INIT_Y (GENERAL_TITLE_HEIGHT)
#define GENERAL_INIT_X 0
#define CALENDAR_INIT_Y (GENERAL_INIT_Y + GENERAL_BOX_HEIGHT + CALENDAR_TITLE_HEIGHT)
#define CALENDAR_INIT_X 0
#define COMMAND_INIT_Y (CALENDAR_INIT_Y + CALENDAR_BOX_HEIGHT +1)
#define COMMAND_INIT_X 0
#define INPUT_START_X 8
#define INPUT_START_Y COMMAND_INIT_Y
#define DIDUKNOW_INIT_X 0
#define DIDUKNOW_INIT_Y (COMMAND_INIT_Y + COMMAND_BOX_HEIGHT)
#define OPERATION_RESULT_Y (DIDUKNOW_INIT_Y +1)
#define OPERATION_RESULT_X 0

#define NUMBER_OF_ENTRY_PARTS 6

//INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR
#define CALENDAR_INDEX_INIT_X 2
#define CALENDAR_DESCRIPTION_INIT_X 6
#define CALENDAR_LOCATION_INIT_X (CALENDAR_TIME_INIT_X - 20)
#define CALENDAR_TIME_INIT_X 85
#define CALENDAR_DATE_INIT_X 99
#define CALENDAR_PRIORITY_INIT_X 113

#define GENERAL_INDEX_INIT_X 2
#define GENERAL_DESCRIPTION_INIT_X 6
#define GENERAL_LOCATION_INIT_X (GENERAL_TIME_INIT_X- 10)
#define GENERAL_TIME_INIT_X 113
#define GENERAL_DATE_INIT_X 113
#define GENERAL_PRIORITY_INIT_X 113

#define MAX_CHAR_LOCATION_CALENDAR (CALENDAR_TIME_INIT_X - CALENDAR_LOCATION_INIT_X -1)
#define MAX_CHAR_DETAIL_CALENDAR (CALENDAR_LOCATION_INIT_X - CALENDAR_DESCRIPTION_INIT_X -1)
#define MAX_CHAR_LOCATION_GENERAL (GENERAL_TIME_INIT_X - GENERAL_LOCATION_INIT_X -1)
#define MAX_CHAR_DETAIL_GENERAL (GENERAL_LOCATION_INIT_X - GENERAL_DESCRIPTION_INIT_X -1)

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED

#define FOOTER_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN

#define TAB 9
#define ENTER 13
#define BACKSPACE 8

#define MAX_INPUT_SIZE (WINDOWS_WIDTH * 2 -9)

using namespace std;

class UI
{
private:

	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;
	static const string ONE_EMPTY_LINE;

	static const string DID_U_KNOW_ADD;
	static const string DID_U_KNOW_DELETE;
	static const string DID_U_KNOW_EXIT;
	static const string DID_U_KNOW_SEARCH;
	static const string DID_U_KNOW_UPDATE;
	static const string DID_U_KNOW_UNDO;
	static const string DID_U_KNOW_HINTS;

	HANDLE hConsole;
	string input;
	Signal focusedField;
	Signal generalDisplayMode;
	Signal calendarDisplayMode;
	Signal diduknowStatus;
	Signal diduknowPrevStatus;
	Signal curStatus;

	int currentChar;
	int generalInitRowIndex;
	int calendarInitRowIndex;
	int diduknowInitRowIndex;
	int generalEndRowIndex; // in case an entry occupies > 1 line, end index is not initial index + box height
	int calendarEndRowIndex;
	int diduknowEndRowIndex;

	void setScreenSize();
	void setBackground();
	void drawBanner();
	void gotoCommandBox();
	void drawCommandBox();
	void clearBox(int startH, int height);
	void gotoxy(int x, int y);
	void writeTitle(string words, int startH, int startW);
	void writeHighlightedTitle(string words,int startH, int startW);
	void highlightTitle(int searchBoxSize);

	void changeDisplayMode();
	void displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void changeFocusedField(vector<string>* resultList);
	void scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void setDidUKnowStatus();

	void initializeDidUKnowStatus();
	void initializeGeneralInitRowIndex(int generalSize);
	void initializeCalendarInitRowIndex(int calendarSize);
	void initializeResultInitRowIndex(int resultSize);

	void extractParts(string entry, string* partArray);
	void printEntryPartMode(int* locationArray, int* colorArray, string* partArray, int index, int rowPosition);
	void printEntryFullMode(int* locationArray, int* colorArray, string* partArray, int index, int& rowPosition, bool& isPrinted);
	void splitPartToLines(string part, int maxLength, int &numnberOfLines, vector<string>* lineVector);
	bool isEnoughSpace(int, int);
	void printLineVector(vector<string>* lineVector);

	void printCalendarEntry(int index, string row, int &rowPosition, bool& isPrinted);
	void printGeneralEntry(int index, string row, int &rowPosition, bool& isPrinted);
	void printResultEntry(int index, string row, int &rowPosition, int sizeOfGeneral, bool& isPrinted);
	void printDiduknowHints();
	bool isGeneral(string row);

	void printContinueFooter();
	void generalEntryListDisplay(vector<string>* generalEntryList);
	void calendarEntryListDisplay(vector<string>* calendarEntryList);
	void resultListDisplay(vector<string>* resultList, int sizeOfGeneral);
	void diduknowHintDisplay();

	void startingScreenDisplay();
public:
	UI(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);

	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);

	string retrieveInput();
	Signal retrieveFocusedField();
	void displayMessage(string message);

	~UI();
};

#endif;