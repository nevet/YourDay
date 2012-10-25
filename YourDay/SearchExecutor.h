#ifndef SEARCHEXECUTOR_H
#define SEARCHEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class SearchExecutor : public Executor
{
private:
	vector<string>* _entryList;
	vector<string>* _matchedEntryList;
	
	vector<string> _undoEntryList;
	vector<string> _undoMatchedEntryList;

	string _details;

public:
	SearchExecutor(vector<string>* entryList, vector<string>* matchedEntryList, string details);

	void execute();
	void undo();
};

#endif