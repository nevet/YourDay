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
	string lowerCasecurRaw ;
	string decodedEntry;
	string kewWord = extractDescription(_details);
	string lowerCaseKeyWord = kewWord;
	transform(kewWord.begin(), kewWord.end(), lowerCaseKeyWord.begin(), tolower);

	for(int i=0;i<_entryList->size();i++)
	{
		curRaw=_entryList->at(i);
		lowerCasecurRaw = curRaw;
		transform(curRaw.begin(),curRaw.end(), lowerCasecurRaw.begin(),tolower);
		if(std::string::npos != lowerCasecurRaw.find(lowerCaseKeyWord))
		{
			_matchedEntryList->push_back(curRaw);
		}
	}
	if(_matchedEntryList->size()==0)
		status = SEARCH_F ;
}

void SearchExecutor::undo()
{
	*_entryList = _undoEntryList;
	*_matchedEntryList = _undoMatchedEntryList;
}