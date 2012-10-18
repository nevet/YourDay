#include "TextObject.h"

TextObject :: TextObject() : Object(ENTRY_TEXT)
{
}

TextObject :: TextObject(string inputText) : Object (ENTRY_TEXT)
{
	text=inputText;
}

void TextObject :: setText(const string inputText)
{
	text=inputText;
}

string TextObject:: getText()
{
	return text;
}

TextObject :: ~TextObject()
{
}