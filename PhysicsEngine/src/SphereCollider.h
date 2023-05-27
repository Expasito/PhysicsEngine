#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
public:

    glm::vec3 position;
    double radius;
    SphereCollider();
    SphereCollider(glm::vec3 pos, double rad);

    void print() {
        std::cout << "Sphere Collider\n";
    }

private:
};

