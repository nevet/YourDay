#include <cassert>
#include <direct.h>

#include "StorageHandler.h"
//@author A0091734A

using namespace std; 


const string StorageHandler::ENTRY_STORE_FORMAT = "%s %s %s\n";
const string StorageHandler::FILEPATH = "YourdayBin/";

const string StorageHandler::DataBaseCalendarFile = "YourDayCEntry.yd";
const string StorageHandler::DataBaseGeneralFile = "YourDayGEntry.yd";
//@author A0091734A 
StorageHandler::StorageHandler()
{
	_mkdir("YourdayBin");

	if(!checkFileExistence(FILEPATH, DataBaseGeneralFile))
		ofstream writeFile(FILEPATH + DataBaseGeneralFile);

	if(!checkFileExistence(FILEPATH, DataBaseCalendarFile))
		ofstream writeFile(FILEPATH + DataBaseCalendarFile);
}

//read data from database
void StorageHandler::readData(vector<string> *ramForGeneralList, vector<string>  *ramForCalendarList)
{	
	assert(ramForGeneralList!=NULL);
	assert(ramForCalendarList!=NULL);

	ifstream infileG(FILEPATH + DataBaseGeneralFile);
	string textLine;
	while(getline(infileG,textLine))
	{
		ramForGeneralList->push_back(textLine);
	}
	infileG.close();

	ifstream infileC(FILEPATH + DataBaseCalendarFile);
	while(getline(infileC,textLine))
	{
		ramForCalendarList->push_back(textLine);
	}
	infileC.close();

	return ;
}
//Write Data into the database
void StorageHandler::writeData(vector<string> *ramForGeneralList, vector<string>  *ramForCalendarList)
{
	assert(ramForGeneralList!=NULL);
	assert(ramForCalendarList!=NULL);

	ofstream clearFileG(FILEPATH + DataBaseGeneralFile);
	ofstream outfileG(FILEPATH + DataBaseGeneralFile,ofstream::app);
	
	for(int i=0;i<ramForGeneralList->size();i++)
	{
		outfileG<<(ramForGeneralList->at(i))<<endl;
	}
	
	

	ofstream clearFileC(FILEPATH + DataBaseCalendarFile);
	ofstream outfileC(FILEPATH + DataBaseCalendarFile,ofstream::app);

	for(int i=0;i<ramForCalendarList->size();i++)
	{
		outfileC<<(ramForCalendarList->at(i))<<endl;
	}
	outfileG.close();
	outfileC.close();

	return ;
}

bool StorageHandler::checkFileExistence(string filePath, string fileName)
{
	fstream testFile;
	bool isExist;
	associateFile(filePath, fileName, testFile, OPEN_TYPE::IN_TYPE);
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
	case IN_TYPE:
		file.open(fileFullPath.c_str(), fstream::in);
		break;
	case OUT_TYPE:
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