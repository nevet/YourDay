#include "Object.h"

Object :: Object() {
}

Object :: Object(int type) {
	objectType=type;
}

int Object :: getType() {
	return objectType;
}

Object :: ~Object() {
}
