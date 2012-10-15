#ifndef SIGNAL_H
#define SIGNAL_H

enum Signal
{
	MASK	= 0xFFFF0000,
	SUCCESS = 0x10000000,
	ERROR	= 0x01000000,
	FAIL    = 0x00100000,
	CLEAR	= 0x00000000,
	
	DISPLAY_E	= ERROR | 0x00000001,
	COMMAND_E	= ERROR | 0x00000002,
	OPTION_E	= ERROR | 0x00000003,
	LENGTH_X_E	= ERROR | 0x00000004,
	LENGTH_Z_E	= ERROR | 0x00000005,	
	EMPTY_ENTRY_E = ERROR | 0x00000006,	//for adding empty string

	ADD_COMMAND		= 0x00000001,
	DELETE_COMMAND	= 0x00000002,
	EDIT_COMMAND	= 0x00000003,
	SEARCH_COMMAND	= 0x00000004,
	UNDO_COMMAND	= 0x00000005,
	EXIT_COMMAND    = 0x00000006,

	ADD_S		= SUCCESS | ADD_COMMAND,
	DELETE_S	= SUCCESS | DELETE_COMMAND,

	ADD_F		= FAIL | ADD_COMMAND,
	DELETE_F	= FAIL | DELETE_COMMAND

//@author a0088455r
//for interpreting commands that is sent drom language handler
	
};

#endif