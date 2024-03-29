/**
    YourDay
    StorageHandler.h
    Purpose: Read from/Write to the database of YourDay.

    @author A0091734A
*/
#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "Signal.h"

#define MAXMIUM_WORDS 255 

enum OPEN_TYPE
{
	APP, IN_TYPE, OUT_TYPE
};
using namespace std;
/**
* StorageHandler is the database handler in the logic component. Storage handler
* would be only called by CommandExecutor and FunctionHandler,which is used to
* store data into the file or read data from file.
* The storage file would be stored as .txt format, but the name would be changed to .yd to protect the content. 
* Only Storage Handler directly access the file system.
*
* @author A0091734A
*/
class StorageHandler
{
public :
	StorageHandler();
	
	/**
	Read the data stored in the file, and put it in a vector of string.
	
	@param the pointer of vector<string> which is used to store the data in the file
	@return void
	*/
	void readData(vector<string>  *ramForGeneralList, vector<string>  *ramForCalendarList);

	/**
	Write the data stored to the file, the data is stored in a vector of string.
	
	@param the pointer of vector<string> which stores the data 
	@return void
	*/
	void writeData(vector<string> *ramForGeneralList, vector<string>  *ramForCalendarList);

private :
	//The maximum words stored for one line/entry.
	char buffer[MAXMIUM_WORDS];

	static const string DataBaseGeneralFile;
	static const string DataBaseCalendarFile;
	static const string FILEPATH;
	static const string ENTRY_STORE_FORMAT;
	
	//@return true->file exists,  false-> file doesn't exist
	bool checkFileExistence(string filePath, string fileName);

	/**
	A series file operations 
	
	@param the name of the file and the the path of file	
	@return void
	*/
	void disassociateFile(fstream & file);
	void associateFile(string filePath, string fileName,
		fstream & file, OPEN_TYPE mode);

	void deleteFile(string filePath, string fileName);
	void renameFile(string filePath, string oriName, string newName);
	void replaceFile(string oriPath, string oriName, string repName);
	//Some of functions above might be used in this version, but may be used in future version.
};


#endif