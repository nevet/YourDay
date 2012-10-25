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
{/*
	matchedEntryList->clear();

	string curRaw;
	string lowerCaseKeyWord = keyWord;
	transform(keyWord.begin(), keyWord.end(), lowerCaseKeyWord.begin(), tolower);

	for(int i=0;i<entryList->size();i++)
	{
		curRaw=entryList->at(i);
		if(std::string::npos != curRaw.find(lowerCaseKeyWord))
		{
			matchedEntryList->push_back(curRaw);
		}
	}*/
}

void SearchExecutor::undo()
{
	*_entryList = _undoEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}