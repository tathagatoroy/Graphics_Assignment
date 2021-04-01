#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->health = 100;
    

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    /* static const GLfloat vertex_buffer_data[] = {
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

        






      
    };*/
    //total 4+7+3 lines
     double pi = 3.14159265;
    int div = 10000;
    int size = div*9;
    double radius = 0.400;
    int traingles = div*3 + 2+2;
    int vertex = 3*traingles;

    GLfloat vertex_buffer_data[3*vertex];
    GLfloat color_buffer_data[3*vertex];
    int ss = 0;
    for(int i=0;i<div;i++)
    {
        double angle_1 = (pi/div)*(double)i;
        double angle_2 = (pi/div)*(double)(i+1);
        //First vertex centre
        vertex_buffer_data[ss] = 0.00;
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = 0.00;
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = 0.00;
        color_buffer_data[ss] = .900;
        ss++;
        //Second vertex
        vertex_buffer_data[ss] = radius*cos(angle_1);
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = radius*sin(angle_1);
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = 0.00;
        color_buffer_data[ss] = .900;
        ss++;
        //third Triangle:
        vertex_buffer_data[ss] = radius*cos(angle_2);
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = radius*sin(angle_2);
        color_buffer_data[ss] = .100;
        ss++;
        vertex_buffer_data[ss] = 0.00;
        color_buffer_data[ss] = .900;
        ss++;
    }
    //RECTANGLE:
    //2 TRIANGLE
    vertex_buffer_data[ss] = radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;

    vertex_buffer_data[ss] = -radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;

    vertex_buffer_data[ss] = -radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = -0.300;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;

   //NEXT TRAINGLE

    vertex_buffer_data[ss] = -radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = -0.300;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;

     vertex_buffer_data[ss] = radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = -0.300;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;


     vertex_buffer_data[ss] = radius;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.000;
    color_buffer_data[ss] = 0.400;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.005;
    ss++;

    //legs 
    vertex_buffer_data[ss] = 0.10;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.50;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    vertex_buffer_data[ss] = 0.40;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.50;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    vertex_buffer_data[ss] = 0.25;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.30;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    vertex_buffer_data[ss] = -0.10;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.50;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    vertex_buffer_data[ss] = -0.40;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.50;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    vertex_buffer_data[ss] = -0.25;
    color_buffer_data[ss] = 0.10;
    ss++;
    vertex_buffer_data[ss] = -0.30;
    color_buffer_data[ss] = 0.800;
    ss++;
    vertex_buffer_data[ss] = 0.00;
    color_buffer_data[ss] = 0.300;
    ss++;

    /*static const GLfloat color_buffer_data[] = {

        0.8,0.2,0.2,
        0.8,0.2,0.2,
        0.8,0.2,0.2,

        0.8,0.2,0.2,
        0.8,0.2,0.2,
        0.8,0.2,0.2,

        0.2,0.2,0.9,
        0.2,0.2,0.9,
        0.2,0.2,0.9,

        0.2,0.9,0.2,
        0.2,0.9,0.2,
        0.2,0.9,0.2,

        0.2,0.9,0.2,
        0.2,0.9,0.2,
        0.2,0.9,0.2
    };*/

    this->object = create3DObject(GL_TRIANGLES, ss/3, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::move_right(){
    this->position.x = this->position.x + 1;

}
void Player::move_left(){
    this->position.x = this->position.x - 1;
}
void Player::move_up(){
    this->position.y = this->position.y + 1;

}
void Player::move_down(){
    this->position.y = this->position.y - 1;
}

void Player::reduce_health(int x){
    this->health += x;
}