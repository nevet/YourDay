#ifndef DELETEEXECUTOR_H
#define DELETEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class DeleteExecutor : public Executor
{
private:
	vector<string>* _entryList;

	string _number;

public:
	DeleteExecutor(vector<string>* entryList, string number);

	void execute();
};

#endif