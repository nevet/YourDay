#ifndef LOG_H
#define LOG_H

# include <string>
# include <fstream>

# include "Signal.h"

using namespace std;

class Log
{
private:

	enum OPEN_TYPE {APP, OUT_TYPE};
	
	fstream file;
	void disassociateFile();
	void associateFile(string fileName, OPEN_TYPE mode);
	
public:
	
	Log();

	void writeCreated(string objName);
	void writeRetrieved(string varName);
	void writeExecuted(string fxName);
	void writeConditionEntered(string condition, bool boolValue);
	
	void writeData(string dataName, string data);
	void writeData(string dataName, Signal data);
	
	void writeException(string exception);
}

#endif