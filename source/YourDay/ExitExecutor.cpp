#include "ExitExecutor.h"
#include <cassert>
ExitExecutor::ExitExecutor(vector<string>* generalEntryList,
						   vector<string>* calendarEntryList,
						   StorageHandler* store, bool* quit)
{	
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(store!=NULL);
	assert(quit!=NULL);

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