#include "Object.h"


Object::Object() {
	position = { 0,0,0 };
	velocity = { 0,0,0 };
}

Object::Object(glm::vec3 pos, glm::vec3 vel) {
	position = pos;
	velocity = vel;
}