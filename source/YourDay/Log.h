#ifndef LOG_H
#define LOG_H

# include <string>
# include <fstream>
# include <time.h>
# include <stdio.h>
# include <vector>
# include <cassert>

# include "Signal.h"

using namespace std;

# define KILO_BYTE 1024
# define SIZE_THRESHOLD 50

class Log
{
private:

	enum OPEN_TYPE {APP_TYPE, OUT_TYPE, IN_TYPE};
	
	fstream file;

	const static string logPath;
	const static string logName;
	const static string fullLogPath;
	const static int sizeThreshold;

	int logSize;

	void disassociateFile();
	void associateFile(string fileName, OPEN_TYPE mode);
	void deleteLogFile();
	
	bool checkLogSize();
	
public:	
	void updateLogFile();

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