#include "ExitExecutor.h"

ExitExecutor::ExitExecutor(vector<string>* generalEntryList,
						   StorageHandler* store, bool* quit)
{
	_generalEntryList = generalEntryList;
	_store = store;
	_quit = quit;
}

void ExitExecutor::execute()
{
	_store->writeData(_generalEntryList);
	
	*_quit = true;
}