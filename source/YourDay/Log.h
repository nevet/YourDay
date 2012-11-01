#ifndef LOG_H
#define LOG_H

# include <string>

# include "Signal.h"

using namespace std;

class Log
{
private:
public:
	void writeCreated(string objName);
	void writeRetrived(string varName);
	void writeExecuted(string fxName);
	void writeConditionEntered(string condition, bool boolValue);
	
	void writeData(string dataName, string data);
	void writeData(string dataName, Signal data);
}

#endif