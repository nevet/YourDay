#ifndef LOG_H
#define LOG_H

# include <string>
# include <fstream>
# include <time.h>
# include <stdio.h>
# include <vector>

# include "Signal.h"

using namespace std;

class Log
{
private:

	enum OPEN_TYPE {APP_TYPE, OUT_TYPE};
	
	fstream file;

	string filePath;
	string fileName;

	void disassociateFile();
	void associateFile(string fileName, OPEN_TYPE mode);

	void checkFileSize();
	
public:

	void writeTime();
	
	void writeCreated(string objName);
	void writeRetrieved(string varName);
	void writeEntered(string fxName);
	void writeExecuted(string fxName);
	void writeConditionEntered(string condition, bool boolValue);
	
	void writeData(string dataName, string data);
	void writeData(string dataName, Signal data);
	void writeData(string dataName, bool data);
	
	void writeException(string exception);
};

#endif