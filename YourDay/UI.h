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

#include "Signal.h"

using namespace std;

class UI
{
private:
	Signal status;
	HANDLE hConsole;
	void setStatus(Signal statusSignal);
public:

	UI();

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
	void mainScreenDisplay();

	~UI();
};

#endif