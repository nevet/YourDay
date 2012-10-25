#ifndef UPDATEEXECUTOR_H
#define UPDATEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class UpdateExecutor : public Executor
{
private:
	vector<string>* _entryList;

	string _details;

public:
	UpdateExecutor(vector<string>* entryList, string details);

	void execute();
};

#endif