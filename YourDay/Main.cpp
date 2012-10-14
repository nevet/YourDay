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
	 bool quit;

	 ui.mainScreenDisplay();

	 while (!quit)
	 {
		 ui.getInput();
		 string userInput = ui.retrieveInput();

		 function.execute(userInput, quit);

		 Signal signal = function.getStatus();
		 ui.displayMessage(signal);
	 }

	 return EXIT_SUCCESS;
}