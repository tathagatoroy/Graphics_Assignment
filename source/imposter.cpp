#include "imposter.h"
#include "main.h"
using namespace std;

Imposter::Imposter(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->alive = 1;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       //SQUARE DONE
       0.25,0.25,0.00,
       0.25,-0.25,0.00,
       -0.25,-0.25,0.00,

       -0.25,-0.25,0.00,
       -0.25,0.25,0.00,
       0.25,0.25,0.00,

       //UPPERTRAINGLE
       0.20,0.25,0.00,
       0.00,0.45,0.00,
       -0.20,0.25,0.00,

        

        //BOTTOM PANTS
        -0.20,-0.25,0.00,
        -0.20,-0.45,0.00,
         0.00,-0.25,0.00,

         0.20,-0.25,0.00,
         0.20,-0.45,0.00,
         0.00,-0.25,0.00

        






      
    };
    //total 4+7+3 lines
    static const GLfloat color_buffer_data[] = {

        0.0,0.92,0.2,
        0.0,0.92,0.2,
        0.0,0.9,0.2,

        0.1,0.92,0.2,
        0.1,0.92,0.2,
        0.1,0.92,0.2,

        0.82,0.2,0.09,
        0.82,0.2,0.09,
        0.82,0.2,0.09,

        0.2,0.009,0.92,
        0.2,0.009,0.82,
        0.2,0.009,0.82,

        0.2,0.009,0.92,
        0.2,0.009,0.82,
        0.2,0.009,0.82
    };

    this->object = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void Imposter::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //cout<<"drawing"<<endl;
    if(this->alive == 1)
    draw3DObject(this->object);
}

void Imposter::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Imposter::move_right(){
    this->position.x = this->position.x + 1;

}
void Imposter::move_left(){
    this->position.x = this->position.x - 1;
}
void Imposter::move_up(){
    this->position.y = this->position.y + 1;

}
void Imposter::move_down(){
    this->position.y = this->position.y - 1;
}

void Imposter::tick(int direction) {
   // cout<<"moving direction"<<direction<<endl;
    if(direction == 1)
    {
        this->move_up();
    }
    else if(direction == 2)
    {
        this->move_down();

    }
    else if(direction == 3)
    {
        this->move_right();

    }
    else if(direction == 4){
        this->move_left();
    }
}
void Imposter::kill(){
    this->alive = 0;
}