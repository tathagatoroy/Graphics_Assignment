#include "main.h"

#ifndef MAZE_H
#define MAZE_H


class Maze {
public:
    Maze() {}
    Maze(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void find_maze(pair<int,int> &current_node,stack<pair> &path,vector<pair<pair<int,int>,pair<int,int>>> &no_walls,vector<int> grid[],pair<int,int> start,int width,int height)
    void create_maze(int height,int width)
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
