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
* Only Storage Handler directly operate the file system.
*/
//@author A0091734A
class StorageHandler
{
public :
	StorageHandler();

	/**
	Sets the status of the language handler after input processing
	
	@param void
	@return void
	*/
	void setStatus();
	
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

	/**
	A series file operations 
	
	@param the name of the file and the the path of file	
	@return void
	*/


	bool checkFileExistence(string filePath, string fileName);
	void disassociateFile(fstream & file);
	void associateFile(string filePath, string fileName,
		fstream & file, OPEN_TYPE mode);
	void deleteFile(string filePath, string fileName);
	void renameFile(string filePath, string oriName, string newName);
	void replaceFile(string oriPath, string oriName, string repName);

	~StorageHandler();

private :
	char buffer[MAXMIUM_WORDS];
	static string DataBaseGeneralFile;
	static string DataBaseCalendarFile; 

	static const string ENTRY_STORE_FORMAT;
	Signal status;


};


#endif