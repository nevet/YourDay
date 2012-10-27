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
*
* @author a00194847U
*/

#include <iostream>
#include <string>
#include "UI.h"
#include "Signal.h"
#include "StatusHandler.h"
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
	UI ui(&calendarEntryList, &generalEntryList);

	//terminating indicator, should be false at the beginning
	bool quit=false;

	while (!quit)
	{
		try
		{
			string userInput = ui.getInput();
			function.execute(userInput, &quit,
							 &generalEntryList,
							 &calendarEntryList,
							 &diduknowBoxList);

			Signal signal = function.getStatus();

			//display updated entries
			ui.mainScreenDisplay(&calendarEntryList, &generalEntryList);
			if(diduknowBoxList.size() == 0)
			{
				ui.diduknowBoxListDisplay(signal);
			}
			else
			{
				ui.diduknowBoxListDisplay(&diduknowBoxList);
			}

			//after one iteration, status of function handler should be cleared
			function.clearStatus();
			}
		catch (string excpt)
		{
			ui.diduknowBoxListDisplay(excpt);
		}
	}

	return EXIT_SUCCESS;
}