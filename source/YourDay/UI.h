//@author A0088469H
/**
* UI class is used for user interact through command line interface
* It traces and passes user input to main(), and control the screen displaying
* Main things to display: general entry list, calendar entry list, search result list, search key word, suggestion key word, 
*	and the "did you know" instruction to user
* Main interaction: tab, up arrow, down arrow, page up key
*/
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

#define INDEX_COLOR FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define DESCRIPTION_COLOR FOREGROUND_INTENSITY |FOREGROUND_BLUE | FOREGROUND_GREEN
#define LOCATION_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED
#define TIME_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define DATE_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN 
#define PRIORITY_COLOR FOREGROUND_INTENSITY | FOREGROUND_RED
#define FOOTER_COLOR FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED
#define HIGHLIGHT_COLOR 1|BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY
#define SPLACHSCREEN_TEXT_COLOR BACKGROUND_RED |15
#define WHITE 15

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
#define SPLASH_POSITION_X 50
#define SPLASH_POSITION_Y 18

#define GENERAL_INIT_Y (GENERAL_TITLE_HEIGHT)
#define GENERAL_INIT_X 0
#define CALENDAR_INIT_Y (GENERAL_INIT_Y + GENERAL_BOX_HEIGHT + CALENDAR_TITLE_HEIGHT)
#define CALENDAR_INIT_X 0
#define COMMAND_INIT_Y (CALENDAR_INIT_Y + CALENDAR_BOX_HEIGHT +1)
#define COMMAND_INIT_X 0
#define INPUT_START_X 8
#define INPUT_START_Y COMMAND_INIT_Y
#define FIRST_LINE_INPUT_WIDTH (WINDOWS_WIDTH - INPUT_START_X)
#define DIDUKNOW_INIT_X 0
#define DIDUKNOW_INIT_Y (COMMAND_INIT_Y + COMMAND_BOX_HEIGHT)
#define OPERATION_RESULT_Y (DIDUKNOW_INIT_Y +2)
#define OPERATION_RESULT_X 0

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

#define TAB 9
#define ENTER 13
#define BACKSPACE 8
#define MOVEMENT_SIGN -32
#define UP_ARROW 72
#define DOWN_ARROW 80
#define PAGE_UP 73

#define NUMBER_OF_ENTRY_PARTS 6
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
	static const string DID_U_KNOW_ADD_LINE1;
	static const string DID_U_KNOW_ADD_LINE2;
	static const string DID_U_KNOW_ADD_LINE3;
	static const string DID_U_KNOW_DELETE_LINE1;
	static const string DID_U_KNOW_DELETE_LINE2;
	static const string DID_U_KNOW_DELETE_LINE3;
	static const string DID_U_KNOW_EXIT;
	static const string DID_U_KNOW_SEARCH;
	static const string DID_U_KNOW_UPDATE_LINE1;
	static const string DID_U_KNOW_UPDATE_LINE2;
	static const string DID_U_KNOW_UNDO;
	static const string DID_U_KNOW_HINTS_LINE1;
	static const string DID_U_KNOW_HINTS_LINE2;
	static const string DID_U_KNOW_HINTS_LINE3;

	//@author A0088469H
	int calendarPositionArray[NUMBER_OF_ENTRY_PARTS];
	int generalPositionArray[NUMBER_OF_ENTRY_PARTS];
	int colorArray[NUMBER_OF_ENTRY_PARTS];

	HANDLE hConsole;
	string input;
	Signal focusedField;
	Signal generalDisplayMode;
	Signal calendarDisplayMode;
	Signal resultDisplayMode;
	Signal diduknowStatus;
	Signal diduknowPrevStatus;
	Signal prevCommand;

	vector<string> calendarList;
	vector<string> generalList;
	vector<string> resultList;

	vector<int> generalInitArrayPart;
	vector<int> generalInitArrayFull;
	vector<int> calendarInitArrayPart;
	vector<int> calendarInitArrayFull;
	vector<int> resultInitArrayPart;
	vector<int> resultInitArrayFull;

	int indexCurGeneralInitArray;
	int indexCurCalendarInitArray;
	int indexCurResultInitArray;

	int highlightGeneralRowIndex;
	int highlightCalendarRowIndex;
	string searchKey;
	vector<string> searchSuggest;

	int currentChar;

	bool isResultDisplay;
	bool isDiduknowDisplay;


	//@author A0088455R
	/**
	* Sets the window size of the program
	* @param void
	* @return void
	**/
	void setScreenSize();

	//@author A0088455R
	/**
	* Sets the background color of a text 
	**/
	void setBackground();
	
	//@author A0088455R
	/*
	* This function draws the Banner of YOURDAY program
	* designed by A0088455R
	*/
	void drawBanner();
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

	//@author A0088469H
	/**This operation is used to display titles with the highlighting
	*/
	void highlightTitle();

	//@author A0088469H
	/** This operation is used to move the cursor to current position of the input the user is typing
	*/
	void gotoCurChar();
	string intToString(int number);

	//@author A0088455R
	/*
	* Initializes the DidUKnow hints box status when the program starts up
	* @param void
	* @return void
	*/
	void initializeDidUKnowStatus();

	//@author A0088469H
	void initializeInitArrayIndices();
	void initializeDisplayModes();
	void initializeFocusedField();
	void initializeHighlightIndices();

	void extractParts(string entry, string* partArray);
	int countPartLine(string part, int maxLength);
	bool isGeneral(string row);
	int findMaxInt(int* intArray, int size);
	int countLineOccupied(string entry, int* maxLengthArray);
	void setInitArrayPart(vector<string> entryList, vector<int>* ansArray, int boxHeight);
	void setInitArrayFull(vector<string> entryList, vector<int>* ansArray, int boxHeight, 
						  int* generalMaxLengthArray, int* calendarMaxLengthArray);
	void setMaxLengthArray(int* locationArray, int size, int* ansArray);
	void setInitialIndexArrays();

	int getGeneralInitIndex();
	int getNextGeneralInitIndex(bool& isValid);
	int getCalendarInitIndex();
	int getNextCalendarInitIndex(bool& isValid);
	int getResultInitIndex();
	int getNextResultInitIndex(bool& isValid);
	int findNearestInitArrayIndex(vector<int>* initialIndexArray, int entryIndex);

	void changeDisplayMode();
	void displayNewMode();
	void changeFocusedField();
	void scrollUp();
	void scrollDown();
	void traceMovementKey();
	void processBackspace();

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

	//@author A0088469H
	/** This operation is used to display the part whose length is limit
	* It is called by printEntryFullMode operation
	* @param part is the part in the string which has limited length
	* @param maxLength is the max length available for the part
	* @param initX, @param initY indicate the beginning position of the part
	* @param endPosition is the end line of the part printed
	*	It is passed by reference and will be feedback at the end of the operation
	*/
	void printLimitedLengthPart(string part, int maxLength, int initX, int initY, int& endPosition);

	/** This operation is used to display an entry when the current displaying mode is 
	*/
	void printEntryPartMode(int* positionArray, int* colorArray, string* partArray, int index, int rowPosition);
	void printEntryFullMode(int* positionArray, int* colorArray, string* partArray, int index, int& rowPosition);
	
	void printMark(string mark);

	//@author A0088469H
	/** This operation is used for printing a calendar entry to screen
	* It will be called by calendarListDisplay(), which will display the whole calendar list
	*	and in resultListDisplay operation if the string needs to be displayed in this operation is in calendar list
	* @param index the up-counting index of this entry in calendar list
	* @param row the entry that needed to be displayed
	* @param rowPosition is passed by reference. This is the vertical position in the screen to print the entry
	*						This is updated if the line occupied by this entry is larger than 1
	*/
	void printCalendarEntry(int index, string row, int &rowPosition);

	/** This operation is used for printing a general entry to screen
	* It will be called by generalEntryListDisplay(), which will display the whole general list
		and in resultListDisplay operation if the string needs to be displayed in this operation is in general list
	* @param index the up-counting index of this entry in general list
	* @param row the entry that needed to be displayed
	* @param rowPosition is passed by reference. This is the vertical position in the screen to print the entry
	*						This is updated if the line occupied by this entry is larger than 1
	*/
	void printGeneralEntry(int index, string row, int &rowPosition);

	/** This operation is used for printing a result entry to screen
	* It will be called by generalEntryListDisplay(), which will display the whole result list
	* It will call printCalendarEntry operation if the entry is in calendar list
	*			or printGeneralEntry operation if the entry is in general list
	* @param index the up-counting index of this entry in result list
	* @param row the entry that needed to be displayed
	* @param rowPosition is passed by reference. This is the vertical position in the screen to print the entry
	*						This is updated if the line occupied by this entry is larger than 1
	*/
	void printResultEntry(int index, string row, int &rowPosition);

	//@author A0088455R
	/**
	* This method prints the didUKnow hints box is a change of didUknow status.
	* @param void
	* @return void
	*/
	void printDiduknowHints();

	//@author A0088469H
	void printGeneralFooter();
	void printCalendarFooter();
	void printResultFooter();

	void generalEntryListDisplay();
	void calendarEntryListDisplay();
	void resultListDisplay();

	//@author A0088455R
	/**
	* This method triggers printing and status change of didUKnow hints box
	* @param void
	* @return void
	*/
	void diduknowHintDisplay();

	//@author A0088469H
	void lockResultDisplay();

	void processResultList(string& info);
	void handleResultInfo(string info);
	void processAddUpdateInfo(string info);
	void processSearchInfo(string info);
	void printSearchInfo();

	void handleInitialGeneralIndexOverflow();
	void handleInitialCalendarIndexOverflow();
	void handleInitialResultIndexOverflow();
	void handleInitialIndicesOverflow();

	/** This operation is used to copy the content of the string vector pointers passed in to corresponding private string vectors of UI
	* It is used in the purpose of storing the entry lists passed in main to private lists used by UI to print to user
	* It is called by mainScreenDisplay, to copy the lists passed from main to mainScreenDisplay to private lists stored in UI
	* The lists copied are calendar entry list, general entry list, and operation result list
	*		Operation result list is the list to store the results of search function, the search key word and suggested key words
	*		in case the user did not type the key word properly
	*		or the string that has just been added/updated by add/update executor
	* @param calendarEntryList is a string vector pointer that point to the vector storing user's calendar entry list
	* @param generalEntryList is a string vector pointer that point to the vector storing user's general entry list
	* @param operationResultList is a string vector pointer that point to the vector storing result list
	*/
	void copyList(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* operationResultList);

	//@author A0088455R
	/*
	* Prints the starting screen
	* @param void
	* @return void
	*/
	void startingScreenDisplay();
public:
	//@author A0088469H
	/** This is the constructor of UI class
	* It will be called in main()
	* It will print out the starting screen and the main screen
	* Initial main screen contains general entry list and calendar entry list,
	* which are stored in the vector passed by main
	* @param calendarEntryList: string vector pointer passed by main, containing user calendar entry list
	* @param generalEntryList: string vector pointer passed by main, containing user general entry list
	* @param operationResultList: string vector pointer passed by main. Initially operationResultList passed by main
	*							will contain nothing but it is not a NULL pointer
	*/
	UI(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* operationResultList);

	void mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* operationResultList);
	void traceInput();

	string retrieveInput();
	Signal retrieveFocusedField();
	void displayMessage(string message);

	~UI();
};

#endif;