/**
* User is allowed to do adding, deleting, searching and updating in our
* program. Input format for each function is listed below:
* 
* To add:
*		add [date] [time] description [at location] [priority ]
* To delete:
*		delete index
* To search:
*		search description
* To update:
*		edit index description
*
* date:
*		DD/MM/YYYY  
* time:
*		HH:MM-HH:MM
* description:
*		no strict format, pure string
* location:
*		no strict format, pure string
* index:
*		positive integer
* priority:
*		can only be one of {high, mid, low}
*/

#include <iostream>
#include <string>
#include "UI.h"
#include "Signal.h"
#include "StatusHandler.h"
#include "FunctionHandler.h"

//This header is for testing purpose
#include "../../testing/Tester.h"

using namespace std;

#define EXIT_SUCCESS 0

/**
* Main() is the over all work flow controller. It knows UIHandler and
* FunctionHandler. It repeatedly calls UIHandler to handler the user input and
* then pass the input to FunctionHandler to handle. If any error happens,
* main() will ask UIHandler to handle the feedback issue.
*/

int main(int arg, char** test)
{
	 
//	runTest(arg,test);

	//recording general entries
	vector<string> generalEntryList;
	//recording calendar entries
	vector<string> calendarEntryList;
	//recording did-u-know box entries
	vector<string> diduknowBoxList;
	
	//create a logger
	Log log;
	
	FunctionHandler function(&generalEntryList, &calendarEntryList, &diduknowBoxList);
	log.writeCreated("FunctionHandler instance");
	
	UI ui;
	log.writeCreated("UI instance created.");

	//terminating indicator, should be false at the beginning
	bool quit=false;

	while (!quit)
	{
		try
		{
			ui.userInteract(&calendarEntryList, &generalEntryList, &diduknowBoxList);
			log.writeCreated("UI interface");
			
			string userInput = ui.retrieveInput();
			log.writeRetrieved("User Input");
			log.writeData("User Input", userInput);
			
			Signal focusingField = ui.retrieveFocusedField();
			log.writeRetrieved("Focus Field");
			log.writeData("Focus Field", focusingField);
			
			function.execute(userInput, &quit, focusingField,
							 &generalEntryList,
							 &calendarEntryList,
							 &diduknowBoxList);
			log.writeExecuted("FunctionHandler::execute()");

			Signal signal = function.getStatus();
		}
		catch (string excpt)
		{
		}
	}
	
	return EXIT_SUCCESS;
}