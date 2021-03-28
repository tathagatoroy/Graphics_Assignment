#include "main.h"

#ifndef SHAPE1_H
#define SHAPE1_H




class Shape1 {
public:
    Shape1() {}
    Shape1(float x, float y, color_t color);
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
