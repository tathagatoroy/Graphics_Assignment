#include "main.h"
using namespace std;
#ifndef MAZE_H
#define MAZE_H
 const int HASH_CONSTANT = 1234;
 const int HEIGHT = 20;
 const int WIDTH = 20;

class Maze {
public:
    Maze() {}
    Maze(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void find_maze(pair<int,int> &current_node,stack <pair<int,int>> &path,vector<pair<pair<int,int>,pair<int,int>>> &no_walls,vector<int> grid[],pair<int,int> start,int width,int height);
    void create_maze(int height,int width);
    int graph[HEIGHT+1][WIDTH+1][HEIGHT+1][WIDTH+1];
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
