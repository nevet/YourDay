#ifndef IO_H
#define IO_H

#include "TextObject.h"
#include "Signal.h"

class IO
{
private:
	TextObject* textObject;
	Signal status;

	void createObject(string text);
	void deleteObject();

	void setStatus(Signal statusSignal);
public:
	IO();

	void getInput();
	void printOutput(TextObject* output);

	void clearStatus();
	Signal getStatus();
	TextObject* retreiveObject();

	~IO();

};

#endif