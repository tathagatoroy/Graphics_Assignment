#include "shape1.h"
#include "main.h"
using namespace std;

double pii = M_PI;

Shape1::Shape1(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    this->status = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        /*-1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
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
        //six horizontal faces
        /*
        cos((0.0f/3)*pi),sin((0.0f/3)*pi),0.0f,
        cos((1.0f/3)*pi),sin((1.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,
        cos((1.0f/3)*pi),sin((1.0f/3)*pi),0.0f,
        cos((2.0f/3)*pi),sin((2.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,
        cos((2.0f/3)*pi),sin((2.0f/3)*pi),0.0f,
        cos((3.0f/3)*pi),sin((3.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,
        cos((3.0f/3)*pi),sin((3.0f/3)*pi),0.0f,
        cos((4.0f/3)*pi),sin((4.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,
        cos((4.0f/3)*pi),sin((4.0f/3)*pi),0.0f,
        cos((5.0f/3)*pi),sin((5.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,
        cos((5.0f/3)*pi),sin((5.0f/3)*pi),0.0f,
        cos((0.0f/3)*pi),sin((6.0f/3)*pi),0.0f, 
        0.0f,0.0f,0.0f,*/
        //six sid faces above the horizontal plane
        cos((0.0f/3)*pii),sin((0.0f/3)*pii),0.0f,
        cos((1.0f/3)*pii),sin((1.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,

        cos((1.0f/3)*pii),sin((1.0f/3)*pii),0.0f,
        cos((2.0f/3)*pii),sin((2.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,
        
        cos((2.0f/3)*pii),sin((2.0f/3)*pii),0.0f,
        cos((3.0f/3)*pii),sin((3.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,

        cos((3.0f/3)*pii),sin((3.0f/3)*pii),0.0f,
        cos((4.0f/3)*pii),sin((4.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,

        cos((4.0f/3)*pii),sin((4.0f/3)*pii),0.0f,
        cos((5.0f/3)*pii),sin((5.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,

        cos((5.0f/3)*pii),sin((5.0f/3)*pii),0.0f,
        cos((0.0f/3)*pii),sin((6.0f/3)*pii),0.0f, 
        0.0f,0.0f,3.0f,

        
        //six side faces below the horizontal plane
        cos((0.0f/3)*pii),sin((0.0f/3)*pii),0.0f,
        cos((1.0f/3)*pii),sin((1.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f,

        cos((1.0f/3)*pii),sin((1.0f/3)*pii),0.0f,
        cos((2.0f/3)*pii),sin((2.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f,

        cos((2.0f/3)*pii),sin((2.0f/3)*pii),0.0f,
        cos((3.0f/3)*pii),sin((3.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f,

        cos((3.0f/3)*pii),sin((3.0f/3)*pii),0.0f,
        cos((4.0f/3)*pii),sin((4.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f,

        cos((4.0f/3)*pii),sin((4.0f/3)*pii),0.0f,
        cos((5.0f/3)*pii),sin((5.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f,

        cos((5.0f/3)*pii),sin((5.0f/3)*pii),0.0f,
        cos((0.0f/3)*pii),sin((6.0f/3)*pii),0.0f, 
        0.0f,0.0f,-3.0f
        
        /*b,a,z,
        -b,a,z,
        z,z,h*/


        
    };
    static const GLfloat color_buffer_data[] = {
      0.1,0.2,0.3,
      0.4,0.5,0.6, 
      0.7,0.8,0.9,

      0.01,0.04,0.09,
      0.16,0.25,0.36,
      0.49,0.64,0.81,

      0.11,0.22,0.33, 
      0.12,0.16,0.20,
      0.11,0.16,0.21,

      0.51,0.27,0.93, 
      0.120,0.46,0.10,
      0.212,0.216,0.321,

      0.351,0.47,0.193, 
      0.20,0.436,0.210,
      0.212,0.1216,0.4321,
      
      0.91,0.82,0.73,
      0.64,0.55,0.46, 
      0.37,0.28,0.19,

      0.81,0.22,0.73,
      0.64,0.25,0.16, 
      0.77,0.28,0.49,

       0.191,0.282,0.373,
      0.464,0.555,0.546, 
      0.437,0.428,0.119,

      0.281,0.122,0.173,
      0.0064,0.125,0.916, 
      0.0077,0.0028,0.0049,

       0.9981,0.9922,0.9973,
      0.7764,0.2225,0.7716, 
      0.6677,0.6628,0.149,

       0.11,0.82,0.73,
      0.44,0.555,0.46, 
      0.47,0.28,0.9,

      0.21,0.12,0.13,
      0.64,0.5,0.916, 
      0.77,0.028,0.9



      



    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Shape1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    //cout<<"x : "<<this->position.x<<" y : "<<this->position.y<<" z : "<<this->position.z<<endl;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Shape1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Shape1::up(){
    this->position.z = this->position.z + 1;
}
void Shape1::down(){
    this->position.z = this->position.z - 1;
}
void Shape1::right(){
    this->position.x = this->position.x + 1;
}
void Shape1::left(){
    this->position.x = this->position.x - 1;
}
void Shape1::front(){
    this->position.y = this->position.y + 1;
}
void Shape1::back(){
    this->position.y = this->position.y - 1;
}
void Shape1::rotate(){
    if(this->status == 0)
        this->status = 1;
    else this->status = 0;
}
void Shape1::tick() {
    
    if(this->status == 1)
    this->rotation += 1;
    //this->position.x -= speed;
    //this->position.y -= speed;
}