/**
* UIHandler is the main handler in the UI component and will be called in main(). UIHandler knows the IO and UI classes
* UIHandler controls the screen displaying and input/output process
* For screen displaying tasks: UIHandler has 2 public APIs startingScreenDisplay():void and mainScreenDisplay():void
* For input/output tasks: UIHandler has APIs getInput():void, retrieveInput():string and displayMessage():void
* UIHandler also has APIs setStatus() and clearStatus() to get and clear status signal
* After each process, UIHandler will set the success/error signal to inform the main()
*/

#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include <vector>
#include "Signal.h"
#include "Handler.h"
#include "UI.h"
#include "IO.h"

using namespace std;

class UIHandler: public Handler
{
private:

	//These are successful display message and will be used in intepreteSignal operation to get the feedback message string
	static const string CLEAR_SIGNAL_MESSAGE;
	static const string ADD_SUCCESSFUL_MESSAGE;
	static const string UPDATE_SUCCESSFUL_MESSAGE;
	static const string DELETE_SUCCESSFUL_MESSAGE;

	//These are error display message and will be used in intepreteSignal operation to get the feedback message string
	static const string DISPLAY_ERROR_MESSAGE;
	static const string COMMAND_ERROR_MESSAGE;
	static const string OPTION_ERROR_MESSAGE;

	static const string DELETE_FAILED_MESSAGE;

	static const string DELETE_ASK_MESSAGE;

	//These are instance of IO and UI class, which will be called in operations of getting input,
	// displaying message and displaying screen
	IO io;
	UI ui;
	
	/**
	* Status signal of command executing process. Signal will be:
	* CLEAR		Testing signal;
	* SUCCESS	Success indicator, all process are successfully handled;
	* ERROR		Error indicator, some errors occured when executing.
	*/
	Signal UIstatus;

	//This attribute is used to store the user input passed from IO class
	string input;

	void setUIStatus(Signal statusSignal);

	/**
	* This operator is used to inteprete the following feedback signal:
	* 	DISPLAY_E, COMMAND_E, OPTION_E, LENGTH_X_E, LENGTH_Z_E, EMPTY_ENTRY_E, 
	*	ADD_S, UPDATE_SDELETE_S
	* to a string feedback message
	* It will be called in displayMessage(string):void operation
	* @param outSignal
	*				is the feedback message passed by the displayMessage operation
	* @return: the feedback message string
	*/
	string interpreteSignal(Signal outSignal);

	/**
	* This operation is used to display the starting screen to the user at the beginning of the program
	* It will call the UI to display starting screen
	*/
	void startingScreenDisplay();
public:

	/**
	* When constructing instance of UIHandler, starting screen should be
	* displayed and saved entries should be displayed on the screen as well
	*/
	UIHandler(vector<string>* entryList);
	void setStatus();
	
	//These are methods to get and print messages

	/**
	* This operation is used to get input message from the user
	* It calls IO to get user input through command line and store it in the private string named input
	*/
	void getInput();

	/**
	* this operation is used to display output message to the user
	* It takes in the feedback signal passed by main(), call private intepreteSignal(Signal):string
	* to inteprete to a string and calls IO to output to the user
	* @param outSignal
	*				is the feedback signal passed by the main() to indicate the success/error in processing command
	*/
	void displayMessage(Signal outSignal);
	void displayMessage(vector<string>* result);
	void displayMessage(string result);
	

	//These are methods to display UI

	/**
	* This operation is used to display the main screen through UI to interact with user
	* It will call the UI to display the main screen
	*/
	void mainScreenDisplay(vector<string>* entryList);

	string retrieveInput();
	Signal getStatus();
	void clearStatus();

	~UIHandler();
};

#endif