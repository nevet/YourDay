//@author A0091847U
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
	//indicates the largest tolerant log file size
	const static int sizeThreshold;

	//the current log file size
	int logSize;

	void disassociateFile();
	void associateFile(string fileName, OPEN_TYPE mode);
	void deleteLogFile();
	
	/**
	* @return true if the current log file exceeds the largest log file size
	*		  tolerance.
	*/
	bool checkLogSize();
	
public:	
	/**
	* This operation is used to limit the size of the log file.
	* 
	* It will delete the old log file and create a new one if the old log file
	* size exceeds 50KB.
	* 
	* This operation is called after every iteration of main loop.
	*/
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