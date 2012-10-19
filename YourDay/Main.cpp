/**
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
	 FunctionHandler function;
	 UIHandler ui;
	 bool quit=false;
	 vector<string>* Ram=function.getEntryList();
	 vector<string> result;	 
	 ui.startingScreenDisplay();

	 ui.mainScreenDisplay(Ram);
	 
	 

	 while (!quit)
	 {
		 ui.getInput();
		 //for debugging using
		 ui.setStatus();
		 string userInput = ui.retrieveInput();

		 function.execute(userInput, quit, &result);

		 Signal signal = function.getStatus();

		 if(signal==EXIT_COMMAND)
			 quit=true;

		 ui.mainScreenDisplay(Ram);
		 ui.displayMessage(&result);
		 ui.displayMessage(signal);
	 }

	 return EXIT_SUCCESS;
}