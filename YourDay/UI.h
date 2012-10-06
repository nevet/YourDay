#ifndef UI_H
#define UI_H

#include "Signal.h"

class UI
{
private:
	Signal status;

	void setStatus(Signal statusSignal);
public:

	UI();

	Signal getStatus();
	void clearStatus();

	void startingScreenDisplay();
	void mainScreenDisplay();

	~UI();
};

#endif