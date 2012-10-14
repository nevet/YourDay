#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <iostream>
#include <vector>
#include "StorageHandler.h"
#include "LangHandler.h"
#include "CommandExecutor.h"

#define MAXIMUM_SIZE 1000

class FunctionHandler:Handler
{
public:
	FunctionHandler();

	void excute(string *input,bool quit);

	~FunctionHandler();

private:
	vector<string> *ram;

};
#endif