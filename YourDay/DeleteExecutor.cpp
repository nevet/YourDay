#include "DeleteExecutor.h"

DeleteExecutor::DeleteExecutor(vector<string>* entryList, string number)
{
	_entryList = entryList;
	_number = number;
}

void DeleteExecutor::execute()
{
	int index;
	
	vector<string>::iterator position;
	
	index=atoi(_number.c_str());
	if(index>_entryList->size())
	{
		status = DELETE_F;
	}
	else 
	{
		position=_entryList->begin()+index-1;
		_entryList->erase(position);
		
		status = DELETE_S;
	}
}