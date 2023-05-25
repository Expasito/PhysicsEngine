#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
public:
    glm::vec3 position;
    glm::vec3 lwh;

    BoxCollider();
    BoxCollider(glm::vec3 pos, glm::vec3 lenwidhei);
private:
};

