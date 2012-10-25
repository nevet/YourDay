/**
* User is allowed to do adding, deleting, searching and updating in our
* program. Input format for each function is listed below:
* 
* To add:
*		add [date] [time] description [at location]
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
*
* @author a00194847U
*/

#include <iostream>
#include <string>
#include "UIHandler.h"
#include "Signal.h"
#include "FunctionHandler.h"
using namespace std;

#define EXIT_SUCCESS 0

/**
* Main() is the over all work flow controller. It knows UIHandler and
* FunctionHandler. It repeatedly calls UIHandler to handler the user input and
* then pass the input to FunctionHandler to handle. If any error happens,
* main() will ask UIHandler to handle the feedback issue.
*/

int main()
{
	//recording general entries
	vector<string> generalEntryList;
	//recording calendar entries
	vector<string> calendarEntryList;
	//recording did-u-know box entries
	vector<string> diduknowBoxList;
	
	FunctionHandler function(&generalEntryList, &calendarEntryList, &diduknowBoxList);
	UIHandler ui(&generalEntryList);

	//terminating indicator, should be false at the beginning
	bool quit=false;

	while (!quit)
	{
		ui.getInput();
		//for debugging using
		ui.setStatus();
		string userInput = ui.retrieveInput();

		function.execute(userInput, &quit,
						 &generalEntryList,
						 &calendarEntryList, 
						 &diduknowBoxList);

		Signal signal = function.getStatus();

		//display updated entries
		ui.mainScreenDisplay(&generalEntryList);
		//display updated did-u-know box list, e.g search resut
		ui.displayMessage(&diduknowBoxList);
		//display caught signals
		if(diduknowBoxList.size()==0)
			ui.displayMessage(signal);

		//after one iteration, status of function handler should be cleared
		function.clearStatus();
	}

	return EXIT_SUCCESS;
}