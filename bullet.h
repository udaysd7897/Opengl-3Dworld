#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y);
    glm::vec3 position;
    float rotation;
    double speed_y,acc_y,speed_x,speed_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void shoot(int *flag,float angle);
    double speed;
private:
    VAO *object;
};

#endif // BULLET_H
