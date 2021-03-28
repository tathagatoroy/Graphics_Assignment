#include "main.h"

#ifndef SHAPE3_H
#define SHAPE3_H




class Shape3 {
public:
    Shape3() {}
    Shape3(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 trans;
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
