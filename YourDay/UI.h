/**
* UI class is used to display User Interface. It is known by UIHandler
* UI has APIs:
*	startingScreenDisplay(): void to display the starting screen at the beginning of the program
*	mainScreenDisplay(): void to display the main screen to interact with the user
*/
#ifndef UI_H
#define UI_H

#include "Signal.h"

class UI
{
private:
	Signal status;

	void setStatus(Signal statusSignal);
public:

	UI();

	Signal getStatus();
	void clearStatus();

	/**
	* This operation is used to show the starting screen to user at the beginning of the program
	* It is called in startingScreenDisplay():void operation in UIHandler class
	*/
	void startingScreenDisplay();

	/**
	* This operation is used to show the main screen to interact with the user
	* It is called in mainScreenDisplay():void operation in UIHandler class
	*/
	void mainScreenDisplay();

	~UI();
};

#endif