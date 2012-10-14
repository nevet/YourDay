#include "StorageHandler.h"

using namespace std; 


const string StorageHandler::ENTRY_STORE_FORMAT = "%s %s %s\n";

string StorageHandler::DataBaseFile = "YourDayEntry.txt";
string StorageHandler::DataBaseTempFile = "YourDayEntryTemp.txt";

StorageHandler::StorageHandler()
{
	ofstream writeFile(DataBaseFile);
}

StorageHandler::~StorageHandler()
{}

void StorageHandler::setStatus()
{
	status = CLEAR;
}

void StorageHandler::readData(vector<string> * ram)
{
	ifstream infile(DataBaseFile);
	string textLine;
	while(getline(infile,textLine))
	{
		ram->push_back(textLine);
	}
	
	infile.close();
	return ;
}

void StorageHandler::writeData(vector<string> *ram)
{
	ofstream outfile(DataBaseFile,ofstream::app);
	outfile.clear();
	for(int i=0;i<ram->size();i++)
	{
		outfile<<(ram->at(i))<<endl;
	}
	outfile.close();
	return ;
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