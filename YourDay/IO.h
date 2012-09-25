#ifndef IO_H
#define IO_H

#include "plainTextObject.h"
#include "Signal.h"

class IO
{
private:
	plainTextObject* textObject;
	Signal status;

	void createObject(string text);
	void deleteObject();

	void setStatus(Signal statusSignal);
	void clearStatus();
public:
	IO();

	void getInput();
	void printOutput(plainTextObject* output);

	Signal getStatus();
	plainTextObject* retreiveObject();

	~IO();

};

#endif