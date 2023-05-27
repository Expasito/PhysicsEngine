#pragma once
#include <glm/vec3.hpp>
#include <iostream>
class Collider
{
	


public:
	glm::vec3 position;


	virtual void print() = 0;

private:
};

