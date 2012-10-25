#ifndef ADDEXECUTOR_H
#define ADDEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;

class AddExecutor : public Executor
{
private:
	vector<string>* _entryList;

	string _details;

public:
	AddExecutor(vector<string>* entryList, string details);

	void execute();
};

#endif