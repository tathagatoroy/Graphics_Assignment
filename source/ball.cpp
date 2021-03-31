#include "ball.h"
#include "main.h"
using namespace std;
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->present = 1; 
    //this->rotation = 0;
    //speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    double pi = 2*3.14159265;
    int div = 10000;
    int size = div*9;
    double radius = 0.4500;

    GLfloat vertex_buffer_data[size];
    GLfloat color_buffer_data[size];
    int ss = 0;
    for(int i=0;i<div;i++)
    {
        double angle_1 = (pi/div)*(double)i;
        double angle_2 = (pi/div)*(double)(i+1);
        //First vertex centre
        vertex_buffer_data[ss] = 0.00;
        //color_buffer_data[ss] = .900;
        ss++;
        vertex_buffer_data[ss] = 0.00;
      //  color_buffer_data[ss] = .900;
        ss++;
        vertex_buffer_data[ss] = 0.00;
      //  color_buffer_data[ss] = .900;
        ss++;
        //Second vertex
        vertex_buffer_data[ss] = radius*cos(angle_1);
       // color_buffer_data[ss] = .200;
        ss++;
        vertex_buffer_data[ss] = radius*sin(angle_1);
       // color_buffer_data[ss] = .300;
        ss++;
        vertex_buffer_data[ss] = 0.00;
       // color_buffer_data[ss] = .400;
        ss++;
        //third Triangle:
        vertex_buffer_data[ss] = radius*cos(angle_2);
     //   color_buffer_data[ss] = .200;
        ss++;
        vertex_buffer_data[ss] = radius*sin(angle_2);
      //  color_buffer_data[ss] = .300;
        ss++;
        vertex_buffer_data[ss] = 0.00;
       // color_buffer_data[ss] = .400;
        ss++;
    }
    /*int r = sizeof(vertex_buffer_data)/(sizeof(GLfloat));
    for(int i=0;i<r;i++)
    {
        if(i%9 == 8)
    {
        cout<<vertex_buffer_data[i]<<endl;
        cout<<endl;
    }
        else if(i%3 == 2 )
    {
        cout<<vertex_buffer_data[i]<<endl;
    }
    else cout<<vertex_buffer_data[i]<<" ";
    }*/

    this->object = create3DObject(GL_TRIANGLES, div*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
   // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //cout<<"present : "<<this->present<<endl;
    if(this->present == 1)
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Ball::eaten(){
    this->present = 0;
}



