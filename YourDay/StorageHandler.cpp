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
