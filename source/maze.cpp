#include "maze.h"
#include "main.h"

int HASH_CONSTANT = 1234;
int HEIGHT = 20;
int WIDTH = 20;

Maze::Maze(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f // triangle 1 : end
      /*  1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f*/
    };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    //Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Maze::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}



void Maze :: find_maze(pair<int,int> &current_node,stack<pair> &path,vector<pair<pair<int,int>,pair<int,int>>> &no_walls,vector<int> grid[],pair<int,int> start,int width,int height){
    if(current_node.vfirst == start.first && current_node.second == start.second && grid[start.first].at(start.second) == 1)
        return;
    else{
        vector<int> dir;
        dir.push_back(1); //NORTH
        dir.push_back(2); //SOUTH
        dir.push_back(3); //EAST
        dir.push_back(4); //WEST
        //visited
        int direction = -1;
        random.shuffle(dir.begin(),dir.end());
        grid[current_node.first].at(current_node.second) = 1;
        pair<int,int> next_node;
        for(int i=0;i<4;i++){
            int d = dir.at(i);

            //NORTH
            if(d == 1){
                int new_y = current_node.first - 1;
                int new_x = current_node.second;
                if(new_y >= 0 && new_y <= (height-1) && grid[new_y].at(new_x) == 0)
                    
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 1;
                    break;

                    
            }
            //SOUTH
            if(d == 2){
                int new_y = current_node.first + 1;
                int new_x = current_node.second;
                if(new_y >= 0 && new_y <= (height-1) && grid[new_y].at(new_x) == 0)
                    
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 2;
                    break;

                    
            }
            //EAST
            if(d == 3){
                int new_y = current_node.first;
                int new_x = current_node.second + 1;
                if(new_x >= 0 && new_x <= (width-1) && grid[new_y].at(new_x) == 0)
                    
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 3;
                    break;

                    
            }
            //WEST
            if(d == 4){
                int new_y = current_node.first;
                int new_x = current_node.second - 1;
                if(new_x >= 0 && new_x <= (width-1) && grid[new_y].at(new_x) == 0)
                    
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 4;
                    break;

                    
            }
        }
        if(dir == -1)
        {
            next_node = path.top();
            path.pop();
        }
        else
        {
            pair<pair<int,int>,pair<int,int>> break_wall;
            break_wall.first = current_node;
            break_wall.second = next_node;
            no_walls.push_back(break_wall);
            path.push(next_node);

        }
        find_maze(next_node,path,no_walls,grid,start,width, height);

        //GOING TO THE NEXT NODE





    }
}
void Maze :: create_maze(int height,int width)
{
    //vector of vector 2D matrix for unvisited nodes
 vector<int> grid[height];
 for(int i=0;i<height;i++){
     for(int j=0;j<width;j++){
         grid[i].push_back(0);
     }
 }
 vector<pair<pair<int,int>,pair<int,int>>> no_walls
 srand(time(NULL));  
 pair<int,int> start;
 start.first = rand() % height;
 start.second = rand() % width;
 stack<pair> path;
 pair<int,int> current_node = start;
 find_maze(current_node,path,no_walls,grid,start,width,height);
 vector<pair<float,float> data_points
 //first the borders;
 //bottom and top
 


}