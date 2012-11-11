# include "Log.h"

const string Log::logPath = "YourdayBin/";
const string Log::logName = "log.txt";
const string Log::fullLogPath = logPath + logName;

const int Log::sizeThreshold = SIZE_THRESHOLD * KILO_BYTE;

void Log::disassociateFile()
{
	if (file.is_open()) file.close();
}

bool Log::associateFile(string fileName, OPEN_TYPE mode)
{
	bool openFail;
	
	switch (mode)
	{
		case IN_TYPE:
			file.open(fileName.c_str(), fstream::in);
			openFail = file.is_open();

			break;
	
		case APP_TYPE:
			file.open(fileName.c_str(), fstream::app);
			
			break;

		case OUT_TYPE:
			file.open(fileName.c_str(), fstream::out);
			
			break;
		default:
			break;
	}

	return openFail;
}

void Log::deleteLogFile()
{
	remove(fullLogPath.c_str());
}

Log::ERROR_TYPE Log::checkLogSize()
{
	bool openFail;

	ERROR_TYPE err = DEFAULT;
	
	openFail = associateFile(fullLogPath.c_str(), IN_TYPE);

	if (!openFail)
	{
		file.seekg(0, fstream::end);
		logSize = file.tellg();

		if (logSize > sizeThreshold)
		{
			err = OVER_SIZE_ERR;
		}

		disassociateFile();
	} else
	{
		err = OPEN_ERR;
	}

	return err;
}

void Log::updateLogFile()
{
	ERROR_TYPE err = checkLogSize();
	
	switch (checkLogSize())
	{
		case OVER_SIZE_ERR:
			deleteLogFile();
			associateFile(fullLogPath, APP_TYPE);

			writeTime();

			break;

		case OPEN_ERR:
			associateFile(fullLogPath, APP_TYPE);

			writeTime();

			break;

		default:
			break;
	}
}

void Log::writeTime()
{
	time_t seconds = time(NULL);
	struct tm * timeinfo = localtime(&seconds);
	
	associateFile(fullLogPath, APP_TYPE);
	
	file << timeinfo->tm_year + 1900 << "/" << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_mday << " ";
	file << timeinfo->tm_hour << ":" <<timeinfo->tm_min << endl;
}

void Log::writeCreated(string objName)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << objName << " is created." << endl;
	
	disassociateFile();
}

void Log::writeRetrieved(string varName)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << varName << " is retrieved." << endl;
	
	disassociateFile();
}

void Log::writeEntered(string fxName)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << fxName << "is entered." << endl;
	
	disassociateFile();
}

void Log::writeExecuted(string fxName)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << fxName << "is executed." << endl;
	
	disassociateFile();
}

void Log::writeConditionEntered(string condition, bool boolValue)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << "condition: " << condition << " is evaluated as " << boolValue << endl;
	
	disassociateFile();
}
	
void Log::writeData(string dataName, string data)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}

void Log::writeData(string dataName, Signal data)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}

void Log::writeData(string dataName, bool data)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << dataName << " = " << data << endl;
	
	disassociateFile();
}
	
void Log::writeException(string exception)
{
	associateFile(fullLogPath, APP_TYPE);
	
	file << "exception threw: " << exception << endl;
	
	disassociateFile();
}