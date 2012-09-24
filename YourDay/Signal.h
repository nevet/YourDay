#ifndef SIGNAL_H
#define SIGNAL_H

enum Signal
{
	MASK	= 0xFFFF0000;
	SUCCESS = 0x00010000;
	ERROR	= 0x00020000;
	
	DISPLAY_E	= ERROR | 0x00000001,
	COMMAND_E	= ERROR | 0x00000002,
	OPTION_E	= ERROR | 0x00000003,
	LENGTH_X_E	= ERROR | 0x00000004,
	LENGTH_Z_E	= ERROR | 0x00000005,

	ADD_S		= SUCCESS | 0x00000001,
	UPDATE_S	= SUCCESS | 0x00000002,
	DELETE_S	= SUCCESS | 0x00000003
};

#endif