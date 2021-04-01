#include "main.h"

#ifndef POWER_H
#define POWER_H


class Power {
public:
    Power() {}
    Power(float x, float y, int score, color_t color);
    glm::vec3 position;
    //float rotation;
    int present ;
    int score;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    //void tick();
    void eaten();
    void activate();
    //double speed;
private:
    VAO *object;
};

#endif // BALL_H
