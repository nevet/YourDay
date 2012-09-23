#ifndef OBJECT_H
#define OBJECT_H

class Object {
protected:
	enum ObjectType (ENTRY_DATE,ENTRY_TIME,ENTRY_DETAILS,ENTRY_INFO);
	int objectType;
public:
	Object();
	Object(int type);
	int getType();
	~Object();
};

#endif