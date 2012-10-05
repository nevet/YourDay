#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <string>
#include "Signal.h"
#include "UI.h"
#include "IO.h"
#include "TextObject.h"

using namespace std;

class UIHandler
{
private:

	/*These are successful display message*/
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
	TextObject* textObject;

	void setStatus(Signal statusSignal);
	void clearStatus();

	void interpreteSignal(Signal outSignal, TextObject* outMessage);
public:

	UIHandler();

	/*These are methods to get and print messages*/
	void getInput();
	void displayMessage(Signal outSignal);

	/*These are methods to display UI*/
	void startingScreenDisplay();
	void mainScreenDisplay();

	TextObject* retreiveObject();
	Signal getStatus();

	~UIHandler()
};

#endif