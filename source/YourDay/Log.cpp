# include "Log.h"

void Log::disassociateFile()
{
	if (file.is_open()) file.close();
}

void Log::associateFile(string fileName, OPEN_TYPE mode)
{
	switch (mode)
	{
		case APP_TYPE:
			file.open(fileName.c_str(), fstream::app);
			
			break;

		case OUT_TYPE:
			file.open(fileName.c_str(), fstream::out);
			
			break;
		default:
			break;
	}
}

void Log::writeTime()
{
	time_t seconds = time(NULL);
	struct tm * timeinfo = localtime(&seconds);
	
	associateFile("log.txt", APP_TYPE);
	
	file << timeinfo->tm_year + 1900 << "/" << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_mday << " ";
	file << timeinfo->tm_hour << ":" <<timeinfo->tm_min << endl;
}

void Log::writeCreated(string objName)
{
	associateFile("log.txt", APP_TYPE);
	
	file << objName << " is created." << endl;
	
	disassociateFile();
}

void Log::writeRetrieved(string varName)
{
	associateFile("log.txt", APP_TYPE);
	
	file << varName << " is retrieved." << endl;
	
	disassociateFile();
}

void Log::writeEntered(string fxName)
{
	associateFile("log.txt", APP_TYPE);
	
	file << fxName << "is entered." << endl;
	
	disassociateFile();
}

void Log::writeExecuted(string fxName)
{
	associateFile("log.txt", APP_TYPE);
	
	file << fxName << "is executed." << endl;
	
	disassociateFile();
}

void Log::writeConditionEntered(string condition, bool boolValue)
{
	associateFile("log.txt", APP_TYPE);
	
	file << "condition: " << condition << " is evaluated as " << boolValue << endl;
	
	disassociateFile();
}
	
void Log::writeData(string dataName, string data)
{
	associateFile("log.txt", APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}

void Log::writeData(string dataName, Signal data)
{
	associateFile("log.txt", APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}

void Log::writeData(string dataName, bool data)
{
	associateFile("log.txt", APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}
	
void Log::writeException(string exception)
{
	associateFile("log.txt", APP_TYPE);
	
	file << "exception threw: " << exception << endl;
	
	disassociateFile();
}