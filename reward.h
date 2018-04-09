#include "main.h"

#ifndef REWARD_H
#define REWARD_H


class Reward {
public:
    Reward() {}
    Reward(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *cannon;
    VAO *cis;
    VAO *trans;
};

#endif // REWARD_H
