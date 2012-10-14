/**
Your Day
UIHandler.h

* This class is used to handle user interface displaying and input/output processes
* Control UI class to display user interface
* Store and pass the user input string passed from IO class
* Control IO class to display feedback message

* @author: Nhu Thao
*/

#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include "Signal.h"
#include "Handler.h"
#include "UI.h"
#include "IO.h"

using namespace std;

class UIHandler:Handler
{
private:

	/*These are successful display message*/
	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	/*These are error display message*/
	static const string DISPLAY_ERROR_MESSAGE;
	static const string COMMAND_ERROR_MESSAGE;
	static const string OPTION_ERROR_MESSAGE;

	IO io;
	UI ui;
	Signal status;
	string input;

	/**
	set the status signal of UIHandler process

	@param the success/error signal to be set to
	@return void
	*/
	void setStatus(Signal statusSignal);

	/**
	inteprete the feedback signal to a string message to show to user

	@param feedback signal
	@return output string message
	*/
	string interpreteSignal(Signal outSignal);
public:

	UIHandler();

	/*These are methods to get and print messages*/

	/**
	get and store the input message from IO
	
	@param void
	@return void
	*/
	void getInput();

	/**
	display feedback message to user through IO

	@param feedback signals from the program after processing user command
	@return void	
	*/
	void displayMessage(Signal outSignal);

	/*These are methods to display UI*/

	/**
	display the starting screen to user through UI at the beginning of the program

	@param void
	@return void
	*/
	void startingScreenDisplay();

	/**
	display the main screen through UI to interact with user

	@param void
	@return void
	*/
	void mainScreenDisplay();

	/**
	retrieve the input string entered by user

	@param void
	@return user input string
	*/
	string retrieveInput();

	/**
	get the status of UIHandler process

	@param void
	@return status signal of UIHandler process
	*/
	Signal getStatus();

	/**
	clear the status signal of UIHandler process to default CLEAR status

	@param void
	@return void
	*/
	void clearStatus();

	~UIHandler()
};

#endif