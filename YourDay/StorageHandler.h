#ifndef STORAGEHANDLER_H
#define STORAGEHANDLER_H

#include "Object.h"
#include "Handler.h"
#include <fstream>
#include <string>
#include <iostream>

#define MAXMIUM_WORDS 255 

using namespace std;
class StorageHandler : Handler
{
public :
	StorageHandler();
	string addEntry(Object);
	string delEntry(Object);
	string updEntry(Object);
	~StorageHandler();


protected :
	char buffer[MAXMIUM_WORDS];
	static string DataBaseFile;
	static string DataBaseTempFile; 

	static const string ENTRY_STORE_FORMAT;
};


#endif