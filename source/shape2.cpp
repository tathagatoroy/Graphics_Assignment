#include "shape2.h"
#include "main.h"


double pi = 2*M_PI;
Shape2::Shape2(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    this->status = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
    
    /*cos((0.0f/11)*pi),sin((0.0f/11)*pi),0.0f,
    cos((1.0f/11)*pi),sin((1.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((0.0f/11)*pi),sin((0.0f/11)*pi),0.0f,
    cos((1.0f/11)*pi),sin((1.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((1.0f/11)*pi),sin((1.0f/11)*pi),0.0f,
    cos((2.0f/11)*pi),sin((2.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((1.0f/11)*pi),sin((1.0f/11)*pi),0.0f,
    cos((2.0f/11)*pi),sin((2.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((2.0f/11)*pi),sin((2.0f/11)*pi),0.0f,
    cos((3.0f/11)*pi),sin((3.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((2.0f/11)*pi),sin((2.0f/11)*pi),0.0f,
    cos((3.0f/11)*pi),sin((3.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((3.0f/11)*pi),sin((3.0f/11)*pi),0.0f,
    cos((4.0f/11)*pi),sin((4.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((3.0f/11)*pi),sin((3.0f/11)*pi),0.0f,
    cos((4.0f/11)*pi),sin((4.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((4.0f/11)*pi),sin((4.0f/11)*pi),0.0f,
    cos((5.0f/11)*pi),sin((5.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((4.0f/11)*pi),sin((4.0f/11)*pi),0.0f,
    cos((5.0f/11)*pi),sin((5.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((5.0f/11)*pi),sin((5.0f/11)*pi),0.0f,
    cos((6.0f/11)*pi),sin((6.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((5.0f/11)*pi),sin((5.0f/11)*pi),0.0f,
    cos((6.0f/11)*pi),sin((6.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((6.0f/11)*pi),sin((6.0f/11)*pi),0.0f,
    cos((7.0f/11)*pi),sin((7.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((6.0f/11)*pi),sin((6.0f/11)*pi),0.0f,
    cos((7.0f/11)*pi),sin((7.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((7.0f/11)*pi),sin((7.0f/11)*pi),0.0f,
    cos((8.0f/11)*pi),sin((8.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((7.0f/11)*pi),sin((7.0f/11)*pi),0.0f,
    cos((8.0f/11)*pi),sin((8.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((8.0f/11)*pi),sin((8.0f/11)*pi),0.0f,
    cos((9.0f/11)*pi),sin((9.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((8.0f/11)*pi),sin((8.0f/11)*pi),0.0f,
    cos((9.0f/11)*pi),sin((9.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((9.0f/11)*pi),sin((9.0f/11)*pi),0.0f,
    cos((10.0f/11)*pi),sin((10.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((9.0f/11)*pi),sin((9.0f/11)*pi),0.0f,
    cos((10.0f/11)*pi),sin((10.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f,



    cos((10.0f/11)*pi),sin((10.0f/11)*pi),0.0f,
    cos((0.0f/11)*pi),sin((0.0f/11)*pi),0.0f,
    0.0f,0.0f,0.0f,

    cos((10.0f/11)*pi),sin((10.0f/11)*pi),0.0f,
    cos((0.0f/11)*pi),sin((0.0f/11)*pi),0.0f,
    0.0f,0.0f,2.0f
   */
    0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    
    0.0f,1.0f,0.0f,
    0.0f,2.0f,0.0f,

    0.0f,2.0f,0.0f,
    1.0f,2.0f,0.0f,

    1.0f,2.0f,0.0f,
    1.0f,1.0f,0.0f,
    
    1.0f,1.0f,0.0f,
    1.0f,0.0f,0.0f,

    1.0f,0.0f,0.0f,
    0.0f,0.0f,0.0f,

    1.0f,1.0f,0.0f,
    0.0f,1.0f,0.0f

        
    };
    static const GLfloat color_buffer_data[] = {
    0.563,0.755,0.544,
0.838,0.952,0.226,
0.225,0.833,0.041,
0.135,0.206,0.782,
0.114,0.477,0.609,
0.711,0.296,0.619,
0.261,0.624,0.106,
/*
0.734,0.414,0.498,
0.094,0.403,0.288,
0.297,0.84,0.095,
0.655,0.629,0.788,
0.899,0.482,0.772,
0.672,0.501,0.553,
0.938,0.458,0.179,
0.795,0.89,0.038,
0.838,0.807,0.294,
0.849,0.708,0.536,
0.106,0.464,0.592,
0.707,0.317,0.788,
0.682,0.726,0.241,
0.921,0.045,0.513,
0.253,0.584,0.44,
0.671,0.239,0.899,
0.356,0.516,0.867,
0.008,0.913,0.948,
0.408,0.164,0.952,
0.487,0.856,0.167,
0.571,0.597,0.567,
0.259,0.151,0.572,
0.009,0.149,0.598,
0.085,0.737,0.441,
0.69,0.484,0.279,
0.712,0.165,0.116,
0.097,0.85,0.839,
0.969,0.156,0.586,
0.869,0.696,0.246,
0.858,0.51,0.828,
0.632,0.607,0.272,
0.668,0.565,0.107,
0.945,0.282,0.226,
0.147,0.856,0.739,
0.572,0.35,0.121,
0.35,0.977,0.753,
0.754,0.964,0.54,
0.202,0.407,0.515,
0.706,0.424,0.507,
0.589,0.058,0.927,
0.313,0.575,0.494,
0.63,0.101,0.284,
0.517,0.043,0.353,
0.881,0.232,0.726,
0.586,0.029,0.47,
0.605,0.724,0.779,
0.194,0.517,0.788,
0.784,0.548,0.726,
0.206,0.981,0.28,
0.776,0.914,0.183,
0.237,0.544,0.876,
0.591,0.519,0.684,
0.734,0.038,0.51,
0.481,0.096,0.12,
0.848,0.408,0.734,
0.499,0.672,0.14,
0.29,0.955,0.461,
0.084,0.339,0.12,
0.292,0.407,0.203
*/
      



    };
    this->object = create3DObject(GL_LINES, 7*2, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Shape2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Shape2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Shape2::up(){
    this->position.z = this->position.z + 1;
}
void Shape2::down(){
    this->position.z = this->position.z - 1;
}
void Shape2::right(){
    this->position.x = this->position.x + 1;
}
void Shape2::left(){
    this->position.x = this->position.x - 1;
}
void Shape2::front(){
    this->position.y = this->position.y + 1;
}
void Shape2::back(){
    this->position.y = this->position.y - 1;
}
void Shape2::rotate(){
    if(this->status == 0)
        this->status = 1;
    else this->status = 0;
}


void Shape2::tick() {
    
    if(this->status == 1)
    this->rotation += 1;
    //this->position.x -= speed;
    //this->position.y -= speed;
}
