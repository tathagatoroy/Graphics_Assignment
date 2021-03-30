#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    //void tick();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
private:
    VAO *object;
};

#endif // BALL_H
