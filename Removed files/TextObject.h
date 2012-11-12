#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include<iostream>
#include <string>

#include "Object.h"

using namespace std;

class TextObject : public Object
{
private:
	string text;
public:
	TextObject();
	TextObject(string inputText);
	void setText(const string inputText);
	string getText();
	~TextObject();
};

#endif