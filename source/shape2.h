#include "main.h"

#ifndef SHAPE2_H
#define SHAPE2_H




class Shape2 {
public:
    Shape2() {}
    Shape2(float x, float y, color_t color);
    glm::vec3 position;
     float rotation;
    int status ;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void up();
    void down();
    void right();
    void left();
    void front();
    void back();
    void rotate();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
