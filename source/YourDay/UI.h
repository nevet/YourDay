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
#define CALENDAR_BOX_HEIGHT (WINDOWS_HEIGHT-GENERAL_TITLE_HEIGHT-GENERAL_BOX_HEIGHT-CALENDAR_TITLE_HEIGHT-COMMAND_BOX_HEIGHT-BOTTOM_BOX_HEIGHT -1) 
// -1 because don't use the line before command box
#define COMMAND_BOX_HEIGHT 2
#define BOTTOM_BOX_HEIGHT 7 
#define DIDUKNOW_HEIGHT 4
#define RESULT_BOX_HEIGHT (WINDOWS_HEIGHT - OPERATION_RESULT_Y -1)

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
#define OPERATION_RESULT_Y (DIDUKNOW_INIT_Y +2)
#define OPERATION_RESULT_X 0

#define NUMBER_OF_ENTRY_PARTS 6

//INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR
#define CALENDAR_INDEX_INIT_X 2
#define CALENDAR_DESCRIPTION_INIT_X 6
#define CALENDAR_LOCATION_INIT_X 65
#define CALENDAR_TIME_INIT_X 85
#define CALENDAR_DATE_INIT_X 99
#define CALENDAR_PRIORITY_INIT_X 113

#define GENERAL_INDEX_INIT_X 2
#define GENERAL_DESCRIPTION_INIT_X 6
#define GENERAL_LOCATION_INIT_X 85
#define GENERAL_TIME_INIT_X 113
#define GENERAL_DATE_INIT_X 113
#define GENERAL_PRIORITY_INIT_X 113

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY |FOREGROUND_BLUE | FOREGROUND_GREEN
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN 
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED

#define FOOTER_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED

#define TAB 9
#define ENTER 13
#define BACKSPACE 8

#define MAX_INPUT_SIZE (WINDOWS_WIDTH * 2 -9)

using namespace std;

class UI
{
private:

	//@author A0088455R
	/**
	* These are the predefined values for hints string
	* These hints are going to be printed at the didUKnow Box
	*/
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
	Signal resultDisplayMode;
	Signal diduknowStatus;
	Signal diduknowPrevStatus;
	Signal prevCommand;

	int currentChar;
	bool isResultDisplay;

	vector<int> generalInitArrayPart;
	vector<int> generalInitArrayFull;
	vector<int> calendarInitArrayPart;
	vector<int> calendarInitArrayFull;
	vector<int> resultInitArrayPart;
	vector<int> resultInitArrayFull;

	int indexCurGeneralInitArray;
	int indexCurCalendarInitArray;
	int indexCurResultInitArray;

	string highlightGeneralRowIndex;
	string highlightCalendarRowIndex;
	string searchKey;
	vector<string> searchSuggest;
	//@author A0088455R
	/**
	* Sets the window size of the program
	* @param void
	* @return void
	**/
	void setScreenSize();
	/**
	* Sets the background color of a text 
	* @param void
	* @return void
	**/
	void setBackground();
	/*
	* This function draws the Banner of YOURDAY program
	* designed by A0088455R
	*/
	void drawBanner();
	void gotoCommandBox();
	void drawCommandBox();
	void clearBox(int startH, int height);

	//@author A0088455R
	/**
	* This method allows the cursor to move to the designated position
	* @param x
	*		is the x coordinate destination
	* @param y
	*		is the y coordinate destionation
	* @return void
	*
	* after this operation, the cursor will move to x,y coordinate in
	* the screen
	*/
	void gotoxy(int x, int y);
	void writeTitle(string words, int startH, int startW);
	void writeHighlightedTitle(string words,int startH, int startW);
	void highlightTitle();

	string intToString(int number);

	//@author A0088455R
	/*
	* Initializes the DidUKnow hints box status when the program starts up
	* @param void
	* @return void
	*/
	void initializeDidUKnowStatus();
	void initializeInitArrayIndices();
	void initializeDisplayModes();
	void initializeFocusedField();

	void extractParts(string entry, string* partArray);
	int countPartLine(string part, int maxLength);
	bool isGeneral(string row);
	void setGeneralInitArrayPart(vector<string>* generalEntryList);
	void setGeneralInitArrayFull(vector<string>* generalEntryList);
	void setCalendarInitArrayPart(vector<string>* calendarEntryList);
	void setCalendarInitArrayFull(vector<string>* calendarEntryList);
	void setResultInitArrayPart(vector<string>* resultList);
	void setResultInitArrayFull(vector<string>* resultList);
	void setInitialIndexArrays(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	//@author A0088455R
	/**
	* This function will set the didUKnow hints box status when there is a change of input
	* @param void
	* @return void
	*
	* This function will change the didUknow status if and only if the user changed their command
	* or backspaces all of his/her input.
	*/
	void setDidUKnowStatus();

	int getGeneralInitIndex();
	int getNextGeneralInitIndex(bool& isValid);
	int getCalendarInitIndex();
	int getNextCalendarInitIndex(bool& isValid);
	int getResultInitIndex();
	int getNextResultInitIndex(bool& isValid);
	int findNearestInitArrayIndex(vector<int>* initialIndexArray, int entryIndex);

	void changeDisplayMode();
	void displayNewMode(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void changeFocusedField();
	void scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	void scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* resultList);
	
	void printLimitedLengthPart(string part, int maxLength, int initX, int initY, int& endPosition);
	void printEntryPartMode(int* positionArray, int* colorArray, string* partArray, string index, int rowPosition);
	void printEntryFullMode(int* positionArray, int* colorArray, string* partArray, string index, int& rowPosition);
	
	void printMark(string mark);
	void printCalendarEntry(int index, string row, int &rowPosition);
	void printGeneralEntry(string index, string row, int &rowPosition);
	void printResultEntry(int& generalIndex, int& calendarIndex, string row, int &rowPosition);
	//@author A0088455R
	/**
	* This method prints the didUKnow hints box is a change of didUknow status.
	* @param void
	* @return void
	*/
	void printDiduknowHints();

	void printGeneralFooter();
	void printCalendarFooter();
	void printResultFooter();

	void generalEntryListDisplay(vector<string>* generalEntryList);
	void calendarEntryListDisplay(vector<string>* calendarEntryList);
	void resultListDisplay(vector<string>* resultList);

	//@author A0088455R
	/**
	* This method triggers printing and status change of didUKnow hints box
	* @param void
	* @return void
	*/
	void diduknowHintDisplay();
	void lockResultDisplay();

	void processResultList(vector<string>* resultList, string& info);
	void handleResultInfo(string info, vector<string>* generalList, vector<string>* calendarList);
	void processAddUpdateInfo(string info, vector<string>* generalList, vector<string>* calendarList);
	void processSearchInfo(string info);
	void printSearchInfo();

	void handleInitialGeneralIndexOverflow();
	void handleInitialCalendarIndexOverflow();
	void handleInitialResultIndexOverflow();
	void handleInitialIndicesOverflow();

	//@author A0088455R
	/*
	* Prints the starting screen
	* @param void
	* @return void
	*/
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