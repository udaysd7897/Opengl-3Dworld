#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void jump(int* flag);
    void turn_left();
    void turn_right();
    float osc();
    double speed;
    double osc_speed;
private:
    VAO *sides;
    VAO *base;
    VAO *cannon;
    VAO *pole;
};

#endif // BOAT_H
