#include "StorageHandler.h"

using namespace std; 


const string StorageHandler::ENTRY_STORE_FORMAT = "%s %s %s\n";

string StorageHandler::DataBaseFile = "YourDayEntry.txt";
string StorageHandler::DataBaseTempFile = "YourDayEntryTemp.txt";

StorageHandler::StorageHandler()
{}

string StorageHandler::addEntry(Object entry)
{
	ofstream writeFile(DataBaseTempFile);	
	
	string EntryDate=entry.getDate();
	string EntryTime=entry.getTime();
	string EntryDetails=entry.getDetails();
	
	sprintf_s(buffer,ENTRY_STORE_FORMAT.c_str(),EntryDate.c_str(),EntryTime.c_str(),EntryDetails.c_str());
	writeFile<<buffer;
	writeFile.close();

	signal=ADD_S;

	return "Entry Added!";
}



string StorageHandler::delEntry(Object entry)
{
	ofstream writeFile(DataBaseTempFile);	

	string EntryDate=entry.getDate();
	string EntryTime=entry.getTime();
	string EntryDetails=entry.getDetails();

	

	signal=DELETE_S;

	return "Entry DELETED!";
}

string StorageHandler::updEntry(Object entry)
{
	ofstream writeFile(DataBaseTempFile);	

	string EntryDate=entry.getDate();
	string EntryTime=entry.getTime();
	string EntryDetails=entry.getDetails();



	signal=UPDATE_S;

	return "Entry Updated!";
}


bool StorageHandler::checkFileExistence(string filePath, string fileName)
{
	fstream testFile;
	bool isExist;
	associateFile(filePath, fileName, testFile, OPEN_TYPE::IN);
	isExist=testFile.is_open();
	disassociateFile(testFile);
	return isExist;
}


void StorageHandler::disassociateFile(fstream & file)
{
	if (file.is_open()) file.close();
}

void StorageHandler::associateFile(string filePath, string fileName,
	fstream & file, OPEN_TYPE mode)
{
	string fileFullPath(filePath+fileName);
	switch (mode)
	{
	case APP:
		file.open(fileFullPath.c_str(), fstream::app);
		break;
	case IN:
		file.open(fileFullPath.c_str(), fstream::in);
		break;
	case OUT:
		file.open(fileFullPath.c_str(), fstream::out);
		break;
	default:
		break;
	}
}


void StorageHandler::deleteFile(string filePath, string fileName)
{
	string fullPath(filePath+fileName);
	remove(fullPath.c_str());
}

void StorageHandler::renameFile(string filePath, string oriName, string newName)
{
	string oriFullPath(filePath+oriName);
	string newFullPath(filePath+newName);
	rename(oriFullPath.c_str(), newFullPath.c_str());
}

void StorageHandler::replaceFile(string oriPath, string oriName, string repName)
{
	deleteFile(oriPath, oriName);
	renameFile(oriPath, oriName, repName);
}