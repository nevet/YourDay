#include "AddExecutor.h"

AddExecutor::AddExecutor(vector<string>* entryList, string details)
{
	_entryList = entryList;
	_details = details;
}

void AddExecutor::execute()
{
	_entryList -> push_back(_details);

	status = ADD_S;
}