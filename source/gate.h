#include "main.h"

#ifndef GATE_H
#define GATE_H




class Gate {
public:
    Gate() {}
    Gate(float x, float y, color_t color);
    glm::vec3 position;
     float rotation;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void rotate();
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
