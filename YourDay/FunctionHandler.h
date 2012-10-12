#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <iostream>
#include <vector>
#include "StorageHandler.h"
#include "LangHandler.h"

#define MAXIMUM_SIZE 1000

class FunctionHandler
{
public:
	FunctionHandler();

	void excute(string input);

	~FunctionHandler();

private:
	vector<string> *ram;

};
#endif