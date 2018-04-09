#include "main.h"

#ifndef MAN_H
#define MAN_H


class Man {
public:
    Man() {}
    Man(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void jump(int* flag);
    void turn_left();
    void turn_right();

    double speed;
private:
    //VAO *object;
    VAO *pole;
    VAO *sphere;
    VAO *limbs;
};

#endif // MAN_H
