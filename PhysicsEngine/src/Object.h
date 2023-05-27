#pragma once
#include <glm/vec3.hpp>
#include "Collider.h"


class Object
{

public:
	glm::vec3 position;
	glm::vec3 velocity;

	Collider* collider;

	Object();
	Object(glm::vec3 pos, glm::vec3 vel);

private:
};

