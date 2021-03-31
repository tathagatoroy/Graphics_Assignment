#include "powerups.h"
#include "main.h"
using namespace std;
Power::Power(float x, float y,int score, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->present = 0; 
    this->score = score;
    //this->rotation = 0;
    //speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    static const GLfloat vertex_buffer_data[] = {
        0.00,0.45,0.00,
        0.00,-0.45,0.00,
        0.45,0.00,0.00,

        0.00,0.45,0.00,
        0.00,-0.45,0.00,
        0.45,0.00,0.00,
    }

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Power::draw(glm::mat4 VP) {
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

void Power::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Power::eaten(){
    this->present = 0;
}
void Power::activate(){
    this->present = 1;
}




