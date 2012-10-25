#include "SearchExecutor.h"

SearchExecutor::SearchExecutor(vector<string>* entryList, vector<string>* matchedEntryList, string details)
{
	_entryList = entryList;
	_matchedEntryList = matchedEntryList;
	_details = details;

	_undoEntryList = *entryList;
	_undoMatchedEntryList = *matchedEntryList;
}

void SearchExecutor::execute()
{
	_matchedEntryList->clear();

	string curRaw;
	string lowerCaseKeyWord = _details;
	transform(_details.begin(), _details.end(), lowerCaseKeyWord.begin(), tolower);

	for(int i=0;i<_entryList->size();i++)
	{
		curRaw=_entryList->at(i);
		if(std::string::npos != curRaw.find(lowerCaseKeyWord))
		{
			_matchedEntryList->push_back(curRaw);
		}
	}
}

void SearchExecutor::undo()
{
	*_entryList = _undoEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}