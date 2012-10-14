/**
Your Day
UI.h

* This class is to display user interface
* Display starting screen to user at the beginning of the program
* Display main screen to interact with user
* author: Nhu Thao
*/
#ifndef UI_H
#define UI_H

#include "Signal.h"

class UI
{
private:
	Signal status;

	/**
	set the status signal of UI displaying process

	@param the status signal to be set to
	@return void
	*/
	void setStatus(Signal statusSignal);
public:

	UI();

	/**
	get the status signal of UI displaying process

	@param void
	@return status signal of UI displaying process
	*/
	Signal getStatus();

	/**
	clear the status signal of IO process to default CLEAR signal

	@param void
	@return void
	*/
	void clearStatus();

	/**
	show the starting screen to user at the beginning of the program

	@param void
	@return void
	*/
	void startingScreenDisplay();

	/**
	show the main screen to interact with the user
	
	@param void
	@return void
	*/
	void mainScreenDisplay();

	~UI();
};

#endif