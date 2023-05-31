#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
public:

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    double radius;
    double mass;
    SphereCollider();
    SphereCollider(glm::vec3 pos, double rad);

    void print() {
        std::cout << "Sphere Collider\n";
    }

private:
};

