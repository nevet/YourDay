#include "ExitExecutor.h"

ExitExecutor::ExitExecutor(vector<string>* generalEntryList,
						   vector<string>* calendarEntryList,
						   StorageHandler* store, bool* quit)
{
	_generalEntryList = generalEntryList;
	_calendarEntryList = calendarEntryList;
	_store = store;
	_quit = quit;
}

void ExitExecutor::execute()
{
	_store->writeData(_generalEntryList, _calendarEntryList);
	
	*_quit = true;
}