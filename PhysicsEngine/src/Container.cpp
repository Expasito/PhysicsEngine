#include "Container.h"

Container::Container() {
	position = { 0,0,0 };
	velocity = { 0,0,0 };
}

Container::Container(glm::vec3 pos, glm::vec3 vel) {
	position = pos;
	velocity = vel;
}

void Container::addChild(Object* object) {
	children.push_back(object);
}