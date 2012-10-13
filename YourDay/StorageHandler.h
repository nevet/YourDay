#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include "Handler.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

#define MAXMIUM_WORDS 255 
enum OPEN_TYPE
{
	APP, IN, OUT
};
using namespace std;
class StorageHandler : Handler
{
public :
	StorageHandler();

	void readData(vector<string> * ram);
	void writeData(vector<string> *ram);
	bool checkFileExistence(string filePath, string fileName);
	void disassociateFile(fstream & file);
	void associateFile(string filePath, string fileName,
		fstream & file, OPEN_TYPE mode);
	void deleteFile(string filePath, string fileName);
	void renameFile(string filePath, string oriName, string newName);
	void replaceFile(string oriPath, string oriName, string repName);

	~StorageHandler();


protected :
	char buffer[MAXMIUM_WORDS];
	static string DataBaseFile;
	static string DataBaseTempFile; 

	static const string ENTRY_STORE_FORMAT;
};


#endif