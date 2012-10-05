#include <iostream>
#include <string>

#include "Handler.h"
#include "Object.h"
#include "DateObject.h"
#include "StatusHandler.h"
#include "UIHandler.h"
#include "LangHandler.h"
#include "StorageHandler.h"

using namespace std;

#define EXIT_SUCCESS 0

/*
This main is simply a skeleton, or pseudo-code... :S
*/

int main()
{
	UIHandler ui;
	LangHandler lang;
	StorageHandler storage;
	StatusHandler status;

	Signal signal;

	Object * obj;
	
	while (1)
	{
		ui.mainScreenDisplay();
		signal = ui.getStatus();

		if (status.success(signal))
		{
			ui.clearStatus();
			ui.getInput();
			signal = ui.getStatus();

			if (status.success(signal))
			{
				obj = ui.retrieveObject();
				lang.seperate(obj);
				signal = lang.getStatus();

				if (status.success(signal))
				{
					obj = lang.retrieve();
					
					switch (static_cast<DetailsObject*>(obj)->getCommand())
					{
						case ADD:
							storage.addEntry(obj);
							signal = storage.getStatus();

							if (status.success(signal))
							{
								ui.successDisplay(signal);
							}
							else
							{
								ui.errorDisplay(signal);
							}

							break;

						case DELETE:
							storage.delEntry(obj);

							if (status.success(signal))
							{
								ui.successDisplay(signal);
							}
							else
							{
								ui.errorDisplay(signal);
							}

							break;

						case UPDATE:
							storage.updEntry(obj);
							
							if (status.success(signal))
							{
								ui.successDisplay(signal);
							}
							else
							{
								ui.errorDisplay(signal);
							}

							break;

						default:
							break;
					}
				}
				else
				{
					ui.errorDisplay(signal);
				}
			}
			else
			{
				ui.errorDisplay(signal);
			}
		}
		else
		{
			ui.errorDisplay(signal);
		}
	}
	
	return EXIT_SUCCESS;
}