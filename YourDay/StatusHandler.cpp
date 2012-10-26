#include "StatusHandler.h"

//Set output strings for successful feedback signals
const string StatusHandler::CLEAR_SIGNAL_MESSAGE = "Command done\n";
const string StatusHandler::ADD_SUCCESSFUL_MESSAGE = "Added successfully\n";
const string StatusHandler::UPDATE_SUCCESSFUL_MESSAGE = "Updated successfully\n";
const string StatusHandler::DELETE_SUCCESSFUL_MESSAGE = "Deleted successfully\n";

//set output strings for error feedback signals on user input
const string StatusHandler::COMMAND_ERROR_MESSAGE = "Wrong command\n";
const string StatusHandler::LENGTH_EXCEED_ERROR_MESSAGE = "Command length exceeded the valid range\n";
const string StatusHandler::LENGTH_ZERO_ERROR_MESSAGE = "Cannot enter command with empty detail\n";
const string StatusHandler::INDEX_ERROR_MESSAGE = "Please enter an index\n";
const string StatusHandler::INVALID_DATE_ERROR_MESSAGE = "Invalid date\n";
const string StatusHandler::INVALID_TIME_ERROR_MESSAGE = "Invalid time\n";
const string StatusHandler::UNDO_ERROR_MESSAGE = "Nothing to undo\n";

//set output strings for error feedback signals on displaying UI
const string StatusHandler::DISPLAY_ERROR_MESSAGE = "Display error\n";

//set output strings for error feedback signals on executing commands
const string StatusHandler::NULL_EXECUTOR_ERROR_MESSAGE = "Executor pointer is NULL\n";
const string StatusHandler::ADD_FAILED_MESSAGE = "Add failed\n";
const string StatusHandler::DELETE_FAILED_MESSAGE = "Delete failed\n";
const string StatusHandler::SEARCH_FAILED_MESSAGE = "Cannot find the key word\n";
const string StatusHandler::UPDATE_FAILED_MESSAGE = "Update failed\n";

string StatusHandler::interpreteSignal(Signal outSignal)
{
	string outString;

	switch (outSignal)
	{
	case CLEAR:
		{
			outString = CLEAR_SIGNAL_MESSAGE;
			break;
		}
	case ADD_S:
		{
			outString = ADD_SUCCESSFUL_MESSAGE;
			break;
		}
	case  DELETE_S:
		{
			outString = DELETE_SUCCESSFUL_MESSAGE;
			break;
		}
	case  UPDATE_S:
		{
			outString = UPDATE_SUCCESSFUL_MESSAGE;
			break;
		}
	case  COMMAND_E:
		{
			outString = COMMAND_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_X_E:
		{
			outString = LENGTH_EXCEED_ERROR_MESSAGE;
			break;
		}
	case  LENGTH_Z_E:
		{
			outString = LENGTH_ZERO_ERROR_MESSAGE;
			break;
		}
	case  INDEX_E:
		{
			outString = INDEX_ERROR_MESSAGE;
			break;
		}
	case  DATE_E:
		{
			outString = INVALID_DATE_ERROR_MESSAGE;
			break;
		}
	case  TIME_E:
		{
			outString = INVALID_TIME_ERROR_MESSAGE;
			break;
		}
	case  DISPLAY_E:
		{
			outString = DISPLAY_ERROR_MESSAGE;
			break;
		}
	case  UNDO_E:
		{
			outString = UNDO_ERROR_MESSAGE;
			break;
		}
	case  EXENULL_E:
		{
			outString = NULL_EXECUTOR_ERROR_MESSAGE;
			break;
		}
	case  ADD_F:
		{
			outString = ADD_FAILED_MESSAGE;
			break;
		}
	case  DELETE_F:
		{
			outString = DELETE_FAILED_MESSAGE;
			break;
		}
	case  SEARCH_F:
		{
			outString = SEARCH_FAILED_MESSAGE;
			break;
		}
	case  UPDATE_F:
		{
			outString = UPDATE_FAILED_MESSAGE;
			break;
		}

	default:
		{
			outString = "";
			break;
		}
	}

	return outString;
}

bool StatusHandler::success(Signal signal)
{
	bool flag;
	
	if ((signal & MASK) == SUCCESS)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}

	return flag;
}

bool StatusHandler::error(Signal signal)
{
	bool flag;

	if ((signal & MASK) == ERR)
	{
		flag = true;
	} else
	{
		flag = false;
	}

	return flag;
}