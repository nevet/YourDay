#include <iostream>
#include <string>
#include "UIHandler.h"
#include "Signal.h"
#include "FunctionHandler.h"
using namespace std;

#define EXIT_SUCCESS 0

int main()
{
	 FunctionHandler function;
	 UIHandler ui;
	 bool quit;

	 //which api should be main screen display?
	 //@Nhu Thao plz change this line if this is incorrect.
	 ui.mainScreenDisplay();

	 while (!quit)
	 {
		 ui.getInput();
		 string* userInput = ui.retreiveInput();

		 function.excute(userInput, quit);

		 Signal signal = function.status();
		 ui.displayMessage(signal);
	 }

	 return EXIT_SUCCESS;
}