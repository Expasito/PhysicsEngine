#pragma once
#include <glm/vec3.hpp>
#include "Object.h"
#include <vector>

/*
* With the Container class, all children coordinates are adjusted by the
* base Container's position
* 
*/
class Container
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	std::vector<Object*> children;

	Container();
	Container(glm::vec3 pos, glm::vec3 vel);

	void addChild(Object* object);
	
private:
};

