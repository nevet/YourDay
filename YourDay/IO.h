#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include "Signal.h"

using namespace std;

class IO
{
private:
	Signal status;
	string text;

	void setText(string inText);
	void setStatus(Signal statusSignal);
public:
	IO();

	void getInput();
	void printOutput(string output);

	void clearStatus();
	Signal getStatus();
	string getText();

	~IO();

};

#endif