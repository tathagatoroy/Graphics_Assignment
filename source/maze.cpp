#include "maze.h"
#include "main.h"
using namespace std;
 

Maze::Maze(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    speed = 0;
    for(int i = 0;i <= HEIGHT;i++){
        for(int j = 0;j<= WIDTH;j++){
            for(int k = 0;k<= HEIGHT;k++){
                for(int l = 0;l <= WIDTH;l++)
                this->graph[i][j][k][l] = 0;
            }
        }
    }
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    /*static const GLfloat vertex_buffer_data[] = {
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
    //};

   // this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
   this->create_maze(HEIGHT,WIDTH);
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



void Maze :: find_maze(pair<int,int> &current_node,stack<pair<int,int>> &path,vector<pair<pair<int,int>,pair<int,int>>> &no_walls,vector<int> grid[],pair<int,int> start,int width,int height){
    if(current_node.first == start.first && current_node.second == start.second && grid[start.first].at(start.second) == 1)
        {//cout<<"Returning From find_maze"<<endl;
        return;
        }
    else{
       // cout<<"Finding Maze at current node "<<current_node.first<<" "<<current_node.second<<endl;
        vector<int> dir;
        dir.push_back(1); //NORTH
        dir.push_back(2); //SOUTH
        dir.push_back(3); //EAST
        dir.push_back(4); //WEST
        //visited
        int direction = -1;
        random_shuffle(dir.begin(),dir.end());
        grid[current_node.first].at(current_node.second) = 1;
        pair<int,int> next_node;
        for(int i=0;i<4;i++){
            int d = dir.at(i);

            //NORTH
            if(d == 1){
                
                int new_y = current_node.first - 1;
                int new_x = current_node.second;
                if(new_y >= 0 && new_y <= (height-1) && grid[new_y].at(new_x) == 0){
                  //  cout<<"NORTH"<<endl;
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 1;
                    break;
                }

                    
            }
            //SOUTH
            if(d == 2){
                
                int new_y = current_node.first + 1;
                int new_x = current_node.second;
                if(new_y >= 0 && new_y <= (height-1) && grid[new_y].at(new_x) == 0){
                    //cout<<"SOUTH"<<endl;
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 2;
                    break;
                }

                    
            }
            //EAST
            if(d == 3){
                
                int new_y = current_node.first;
                int new_x = current_node.second + 1;
                if(new_x >= 0 && new_x <= (width-1) && grid[new_y].at(new_x) == 0){

                
                //    cout<<"EAST"<<endl;
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 3;
                    break;
                }

                    
            }
            //WEST
            if(d == 4){
                
                int new_y = current_node.first;
                int new_x = current_node.second - 1;
                if(new_x >= 0 && new_x <= (width-1) && grid[new_y].at(new_x) == 0){
                 //   cout<<"WEST"<<endl;
                    next_node.first = new_y;
                    next_node.second = new_x;
                    direction = 4;
                    break;
                }

                    
            }
        }
        if(direction == -1)
        {
         //   cout<<"BACK"<<endl;

            next_node = path.top();
            path.pop();
         //   cout<<"EXIT"<<endl;
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
  //  cout<<"CALLING CREATE_MAZE"<<endl;
 vector<int> grid[height];
 for(int i=0;i<height;i++){
     for(int j=0;j<width;j++){
         grid[i].push_back(0);
     }
 }
 vector<pair<pair<int,int>,pair<int,int>>> no_walls;
 srand(time(NULL));  
 pair<int,int> start;
 start.first = rand() % height;
 start.second = rand() % width;
 stack<pair<int,int>> path;
 path.push(start);
 pair<int,int> current_node = start;
 find_maze(current_node,path,no_walls,grid,start,width,height);
 //cout<<"Find MAZE() done"<<endl;
 vector<pair<float,float>> data_points;
 //first the borders;
 //bottom and top 
 float ini = 0.00;
 float hini = (float)height*1.00;
 for(int i=0;i<width;i++){
     pair<float,float> t1,t2;
     pair<float,float> b1,b2;
     t1.first = 0.00;
     t2.first = 0.00;
     t1.second = ini;
     t2.second = ini + 1.00;
     b1.first = hini;
     b2.first = hini;
     b1.second = ini;
     b2.second = ini + 1.00;
     ini += 1.00;
     data_points.push_back(b1);
     data_points.push_back(b2);
//     cout<<"from ("<<b1.second<<","<<b1.first<<") to ("<<b2.second<<","<<b2.first<<")"<<endl;

     
     data_points.push_back(t1);
     data_points.push_back(t2);
 //   cout<<"from ("<<t1.second<<","<<t1.first<<") to ("<<t2.second<<","<<t2.first<<")"<<endl;


 }
 //Left and Right Sids;
 ini = 0.00;
 hini = (float)width*1.00;
 for(int i=0;i<height;i++){
     pair<float,float> t1,t2;
     pair<float,float> b1,b2;
     t1.second = 0.00;
     t2.second = 0.00;
     t1.first = ini;
     t2.first = ini + 1.00;
     b1.second = hini;
     b2.second = hini;
     b1.first = ini;
     b2.first = ini + 1.00;
     ini += 1.00;
     data_points.push_back(b1);
     data_points.push_back(b2);
 //   cout<<"from ("<<b1.second<<","<<b1.first<<") to ("<<b2.second<<","<<b2.first<<")"<<endl;

     data_points.push_back(t1);
     data_points.push_back(t2);

  //  cout<<"from ("<<t1.second<<","<<t1.first<<") to ("<<t2.second<<","<<t2.first<<")"<<endl;


 }
 //NOW ALL HORIZONTAL WALLS
 int erasing = 0;
 for(int i=1;i<height;i++)
 {
     for(int j=0;j<width;j++){
         //wall between (i-1,j) and (i,j)
         int size = no_walls.size();
         int allowed = 1;
         for(int k=0;k<size;k++){
             pair<int,int> v1 = no_walls.at(k).first;
             pair<int,int> v2 = no_walls.at(k).second;
             if(v1.second == j && v2.second == j && ((v1.first == i-1 && v2.first == i) || (v1.first == i && v2.first == i-1)))
               { 
                   allowed = 0;
                   erasing ++;
                 //  cout<<"Erasing wall "<<erasing<<endl;
                 break;
               }
         }
         if(allowed == 1){
             pair<float,float> f;
             f.first = i;
             f.second = j;
             data_points.push_back(f);
             
             f.second ++;
             data_points.push_back(f);
           //  cout<<"from ("<<f.second-1<<","<<f.first<<") to ("<<f.second<<","<<f.first<<")"<<endl;

         }
     }
 }
 //NOW ALL VERTICAL WALLS
 for(int i=1;i<width;i++)
 {
     for(int j=0;j<height;j++){
         //wall between (j,i+1),(j,i)
         int size = no_walls.size();
         int allowed = 1;
         for(int k=0;k<size;k++){
             pair<int,int> v1 = no_walls.at(k).first;
             pair<int,int> v2 = no_walls.at(k).second;
             if(v1.first == j && v2.first == j && ((v1.second == i-1 && v2.second == i) || (v1.second == i && v2.second == i-1)))
               { allowed = 0;
                 erasing ++;
             //   cout<<"Erasing wall "<<erasing<<endl;

                 break;
               }
         }
         if(allowed == 1){
             pair<float,float> f;
             f.first = j;
             f.second = i;
             data_points.push_back(f);
             f.first ++;
             data_points.push_back(f);
            //  cout<<"from ("<<f.second<<","<<f.first-1<<") to ("<<f.second<<","<<f.first<<")"<<endl;
         }
     }
 }
 int k = (data_points.size()/2);
 GLfloat vertex_buffer[6*k];
 int ss = 0;
 int ff = 0;
 for(int i=0;i<2*k;i= i+2)
 {
     float distance = 0;
   vertex_buffer[ss] = data_points.at(i).second;
   ss++;
   vertex_buffer[ss] = data_points.at(i).first;
   ss++;
   vertex_buffer[ss] = 0.00;
   ss++;
   vertex_buffer[ss] = data_points.at(i+1).second;
   ss++;
   vertex_buffer[ss] = data_points.at(i+1).first;
   ss++;
   vertex_buffer[ss] = 0.00;
   ss++;
  // cout<<" wall : "<<ff<<endl;
   ff++;
   this->graph[(int)data_points.at(i).first][(int)data_points.at(i).second][(int)data_points.at(i+1).first][(int)data_points.at(i+1).second] = 1;
   this->graph[(int)data_points.at(i+1).first][(int)data_points.at(i+1).second][(int)data_points.at(i).first][(int)data_points.at(i).second] = 1;

 /*  cout<<data_points.at(i).second<<" "<<data_points.at(i).first<<" "<<0.00<<endl;
   cout<<data_points.at(i+1).second<<" "<<data_points.at(i+1).first<<" "<<0.00<<endl;
   cout<<endl;*/
   
 }
 /*cout<<"TOTAL WALLS :"<<2*width*height+height+width<<endl;
 cout<<"ACTUAL WALLS:"<<k<<endl;
 cout<<"WALLS ERASED "<<no_walls.size()<<endl;
 int z = no_walls.size();
 for(int i=0;i<z;i++){
     pair<int,int> x = no_walls.at(i).first;
     pair<int,int> y = no_walls.at(i).second;
     cout<<i<<endl;
     cout<<"NO WALLS BETWEEN ("<<x.second<<","<<x.first<<") and ("<<y.second<<","<<y.first<<")"<<endl;
 }*/
 this->object = create3DObject(GL_LINES, k*2, vertex_buffer, COLOR_RED, GL_FILL);

 


}