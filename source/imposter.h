#include "main.h"

#ifndef IMPOSTER_H
#define IMPOSTER_H


class Imposter {
public:
    Imposter() {}
    Imposter(float x, float y, color_t color);
    glm::vec3 position;
    int alive ;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int direction);
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void kill();
private:
    VAO *object;
};

#endif // BALL_H
