#include "main.h"
#include "timer.h"
#include "ball.h"
#include "shape1.h"
#include "shape2.h"
#include "shape3.h"
#include "glm/ext.hpp"
#include "maze.h"
#include "player.h"
#include "imposter.h"
#include "powerups.h"
#include "shader.h"
#include <ft2build.h>
#include "gate.h"
#include FT_FREETYPE_H
int end_time = 0;
FT_Library  library;   /* handle to library     */
FT_Face     face;      /* handle to face object */
map<GLchar, Character> Characters;
unsigned int vao, vbo;


const int num_health = 3;


using namespace std;

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Ball ball2;//powerup button
Ball ball1; // kill villain
Shape1 first;
Maze second; //maze ,sorry for the stupid name.Carried over from last assignment
Shape3 third;
Player hero;
Imposter villain;
Power obstacles[num_health];
Power health[num_health];
Gate gate;
int object = -1;
int status = -1;
int iteration = 0;

 int total_tasks = 11;
 int tasks_completed = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float camera_x = 10;
float camera_y = 10;
float camera_z = 35;
float target_x = 10;
float target_y = 10;
float target_z = 0;
float rotate1 = 0;


Timer t60(1.0 / 60);

void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void end_game(int r,Shader &shader)
{
      //  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //position of camera  (5,0,0)
    
                
    glm::vec3 eye (camera_x, camera_y,camera_z);
    //cout<<glm::to_string(eye) ;
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x,target_y,target_z);
    glm::vec3 direction = glm::normalize(eye-target);
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    Matrices.projection = glm::perspective(glm::radians(45.0f), (float) 600 / (float) 600, 0.1f, 100.0f);   // Far clipping plane. Keep as little as possible.);
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    second.draw(VP);

    char buf[100];
    if(r == 1)
    sprintf(buf,"GAME OVER ,YOU WON,FINISHED ALL TASKED AND MANAGED TO EXIT");
    else if(r==0) 
    sprintf(buf,"GAME OVER, TIME OVER ,YOU LOST");
    else if(r == -1)
    sprintf(buf,"GAME OVER, NO HEALTH LEFT,YOU LOST");
    string ss;
            int len = strlen(buf);
            for(int i = 0 ;i< len;i++)
            ss.push_back(buf[i]);
              glEnable(GL_BLEND);
            cout<<ss<<endl;
            RenderText(shader, ss, 25.0f, 540.0f, 0.30f, glm::vec3(0.5, 0.8f, 0.2f));
           // RenderText(shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
            glDisable(GL_BLEND);

            usleep(10000000);
            exit(1);
    

}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //position of camera  (5,0,0)
    
                
    glm::vec3 eye (camera_x, camera_y,camera_z);
    //cout<<glm::to_string(eye) ;
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x,target_y,target_z);
    glm::vec3 direction = glm::normalize(eye-target);
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    Matrices.projection = glm::perspective(glm::radians(45.0f), (float) 600 / (float) 600, 0.1f, 100.0f);   // Far clipping plane. Keep as little as possible.);
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
      
    // Scene render
  
    second.draw(VP);
    
  //  cout<<villain.alive<<endl;
  
  //    cout<<"DRAWING VILLAIN"<<endl;
    
    
    
    ball1.draw(VP);
    ball2.draw(VP);
    for(int i=0;i<num_health;i++){
        health[i].draw(VP);
        obstacles[i].draw(VP);
    }
    gate.draw(VP);
    villain.draw(VP);
    hero.draw(VP);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{//move objects
/*cout<<"object "<<object<<endl;
if(object == 3)
{
   if(key == GLFW_KEY_A && action == GLFW_PRESS)
   third.up();
  */
  if(key == GLFW_KEY_W && action == GLFW_PRESS){
      int cur_x = (int)hero.position.x;
      int cur_y = (int)hero.position.y;
      int next_y = (int)(hero.position.y+1);
      int next_x = cur_x;
      /*
      wall between (y,x),(y+1,x) is horizontal wall is (y+1,x) and (y+1,x+1)
      */
      if(next_y <= HEIGHT && second.graph[next_y][cur_x][next_y][cur_x + 1] == 0)
        hero.move_up();
  }
  if(key == GLFW_KEY_A && action == GLFW_PRESS){
      int cur_x = (int)hero.position.x;
      int cur_y = (int)hero.position.y;
      int next_y = (int)hero.position.y;
      int next_x = cur_x - 1;
      /*
      wall between (y,x),(y,x-1) is vertical wall is (y,x) and (y+1,x)
      */
      if(next_x >= 0 && second.graph[cur_y][cur_x][cur_y + 1][cur_x] == 0)
        hero.move_left();
  }
  if(key == GLFW_KEY_S && action == GLFW_PRESS){
      int cur_x = (int)hero.position.x;
      int cur_y = (int)hero.position.y;
      int next_y = (int)hero.position.y-1;
      int next_x = cur_x;
      /*
      wall between (y,x),(y-1,x) is horizontal wall is (y,x) and (y,x+1)
      */
      if(next_y >= 0 && second.graph[cur_y][cur_x][cur_y][cur_x + 1] == 0)
        hero.move_down();
  }
  if(key == GLFW_KEY_D && action == GLFW_PRESS){
      int cur_x = (int)hero.position.x;
      int cur_y = (int)hero.position.y;
      int next_y = (int)hero.position.y;
      int next_x = cur_x + 1;
      /*
      wall between (y,x),(y,x+1) is vertical wall is (y,x+1) and (y+1,x+1)
      */
      if(next_x <= WIDTH && second.graph[cur_y][cur_x+1][cur_y + 1][cur_x+1] == 0)
        hero.move_right();
  }

  if(key == GLFW_KEY_T && action == GLFW_PRESS){
      int z = rand() % 400;
      int y = z % 20;
      int x = z / 20;
      float y1 = (int)y + 0.50;
      float x1 = (int)x + 0.50;
      hero.set_position(x1,y1);
  }
  if(key == GLFW_KEY_Q && action == GLFW_PRESS){
      exit(1);
  }
  
}
   


void tick_elements() {


    //ball1.tick();
int cur_x = (int)hero.position.x;
int cur_y  = (int)hero.position.y;
int button_x = (int)ball1.position.x;
int button_y = (int)ball1.position.y;
int pow_x = (int)ball2.position.x;
int pow_y = (int)ball2.position.y;
int g_x = (int)gate.position.x;
int g_y = (int)gate.position.y;
int v_x = (int)villain.position.x;
int v_y = (int)villain.position.y;

if(villain.alive == 1 && v_x == cur_x && v_y == cur_y)
{
    end_time = time(NULL);
    status = -1;
}
if(cur_x == g_x && cur_y == g_y && tasks_completed == total_tasks)
{
   end_time = time(NULL);
   status = 1;
}

//check you can kill the villain
if(cur_x == button_x && button_y == cur_y && ball1.present == 1)
{
    villain.kill();
    ball1.eaten();
   // cout<<"VILLAIN DEAD"<<endl;
}
//check you can activate powerups
if(cur_x == pow_x && cur_y == pow_y && ball2.present == 1){
    ball2.eaten();
    for(int i=0;i<num_health;i++){
        health[i].activate();
        obstacles[i].activate();
    }
    cout<<"ACTIVATE"<<endl;
}
//checking whether gained some powerups
for(int i = 0;i<num_health;i++)
{
    int h_x = (int)health[i].position.x;
    int h_y = (int)health[i].position.y;
    if(cur_x == h_x && cur_y == h_y && health[i].present == 1)
    {
        health[i].eaten();
        hero.reduce_health(health[i].score);
      //  cout<<"HEALTH GAINED"<<endl;

    }

}
for(int i = 0;i<num_health;i++)
{
    int h_x = (int)obstacles[i].position.x;
    int h_y = (int)obstacles[i].position.y;
    if(cur_x == h_x && cur_y == h_y && obstacles[i].present == 1)
    {
        obstacles[i].eaten();
        hero.reduce_health(obstacles[i].score);
      //  cout<<"HEALTH LOST"<<endl;

    }
    //cout<<"HEALTH LOST"<<endl;

}

if(villain.alive == 1){
    int v_x = (int)villain.position.x;
    int v_y = (int)villain.position.y;
    int dir = -1;
    int mini = 1e6;
    //NORTH
    if(v_y + 1 < HEIGHT)
    {
        if(second.distance[v_y][v_x][v_y + 1][v_x] == 1){
            if(second.distance[v_y + 1][v_x][cur_y][cur_x] < second.distance[v_y][v_x][cur_y][cur_x])
            {
            // cout<<"NORTH"<<endl;
                dir = 1;
                mini = second.distance[v_y + 1][v_x][cur_y][cur_x];
            }
        }
    }
    //SOUTH
    if(v_y - 1 >= 0)
    {
        if(second.distance[v_y][v_x][v_y - 1][v_x] == 1){
            if(second.distance[v_y - 1][v_x][cur_y][cur_x] < second.distance[v_y][v_x][cur_y][cur_x])
            {
            //  cout<<"SOUTH"<<endl;
                dir = 2;
                mini = second.distance[v_y - 1][v_x][cur_y][cur_x];
            }
        }
    }
    //WEST
    if(v_x + 1 < WIDTH)
    {
        if(second.distance[v_y][v_x][v_y][v_x + 1] == 1){
            if(second.distance[v_y][v_x + 1][cur_y][cur_x] < second.distance[v_y][v_x][cur_y][cur_x])
            {
                //cout<<"WEST"<<endl;
                dir = 3;
                mini = second.distance[v_y][v_x + 1][cur_y][cur_x];
            }
        }
    }
    //EAST
    if(v_x - 1 < WIDTH)
    {
        if(second.distance[v_y][v_x][v_y][v_x - 1] == 1){
            if(second.distance[v_y][v_x - 1][cur_y][cur_x] < second.distance[v_y][v_x][cur_y][cur_x])
            {
            //   cout<<"EAST"<<endl;
                dir = 4;
                mini = second.distance[v_y][v_x - 1][cur_y][cur_x];
            }
        }
    }
    if(iteration % 50 == 0)
    villain.tick(dir);
    else
    villain.tick(-1);
    gate.tick();
}


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    int num = rand() % 400;//height *width;
        int y = num / 20;
        float y1 = (float)y + 0.50;
        int x = num % 20;
        float x1 = (float)x + 0.50;

    ball1       = Ball(x1, y1, COLOR_GREEN);

    num = rand() % 400;//height *width;
     y = num / 20;
     y1 = (float)y + 0.50;
     x = num % 20;
     x1 = (float)x + 0.50;
    ball2       = Ball(x1,y1,COLOR_THREE);


    second    = Maze(0, 0, COLOR_RED);


    num = rand() % 400;//height *width;
     y = num / 20;
     y1 = (float)y + 0.50;
     x = num % 20;
     x1 = (float)x + 0.50;
    //first         = Shape1(0,0,COLOR_RED);
    //third       = Shape3(0,0, COLOR_RED);
    hero       = Player(x1,y1,COLOR_RED);

    num = rand() % 400;//height *width;
     y = num / 20;
     y1 = (float)y + 0.50;
     x = num % 20;
     x1 = (float)x + 0.50;
    villain    = Imposter(x1,y1,COLOR_RED);

    num = rand() % 400;//height *width;
     y = num / 20;
     y1 = (float)y + 0.50;
     x = num % 20;
     x1 = (float)x + 0.50;
     gate = Gate(x1,y1,COLOR_BLACK);
    for(int i = 0;i < num_health; i++ )
    {
        int num = rand() % 400;//height *width;
        int y = num / 20;
        float y1 = (float)y + 0.50;
        int x = num % 20;
        float x1 = (float)x + 0.50;
        int num1 = rand() % 400;
        int a = num1 / 20;
        float a1 = (float)a + 0.50;
        int b = num1 % 20;
        float b1 = (float)b + 0.50;
        health[i] = Power(x1,y1,10,COLOR_GOLD);
        obstacles[i] = Power(b1,a1,-10,COLOR_ONE);

    }

    //create a adjacent list from the maze graph


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (2.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main() {
    /*vec3 light(0.0f, 0.0f, 0.0f);
    light.x = player.position.x;
    light.y = player.position.y;
    light.z = player.position.z;*/
    srand(time(0));
    int width  = 600;
    int height = 600;
    window = initGLFW(width, height);

    initGL (window, width, height);

    glfwSetKeyCallback(window, key_callback);
 
    //creates the window

    //stuff related to FREETYPE 
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Shader shader("/home/tathagato/Hello-World/source/text.vs", "/home/tathagato/Hello-World/source/text.fs");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    if (FT_Init_FreeType(&library)){

        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
        return -1;
    }

    if(FT_New_Face( library,"/usr/share/fonts/truetype/freefont/FreeSans.ttf",0,&face )){
        cout<<"Error Loading Font"<<endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48); 
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)){

        cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;  
        return -1;
    }
    

    //COPIED FOR FREETYPE

    FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(library);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    int start_time = time(NULL);
     end_time = start_time + 500;
     total_tasks = num_health + 1;

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
       // iteration ++;
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            //glEnable(GL_BLEND);
          //  if(end_time <= time(NULL))
          //  end_game(0,shader);
           // draw();
            iteration ++;

            //creating the string to render the

             tasks_completed = 0;
             for(int i=0;i<num_health;i++){
                 if(health[i].present == -1){
                     tasks_completed++;
                 }
               /*  if(obstacles[i].present == -1){
                     tasks_completed++;
                 }*/
             } 
             if(villain.alive == 0){
                 tasks_completed++;
             }
             char print_out[100];
             int time_left = end_time - time(NULL);
             if(time_left < -2)
             exit(1);
            else if(time_left > 0)
            { 
                sprintf(print_out,"HEALTH : %d  TASK COMPLETED : %d TASK LEFT : %d LIGHT: ON TIME_LEFT : %d",hero.health,tasks_completed,total_tasks-tasks_completed,time_left);
                draw();
            }
            else 
             {  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
             if(status == 1)
                sprintf(print_out,"CONGRAGULATIONS , YOU WON");
                else
                 sprintf(print_out,"GAME OVER,TIMES UP,YOU LOST");
             }
            string ss;
            int len = strlen(print_out);
            for(int i = 0 ;i< len;i++)
            ss.push_back(print_out[i]);
            cout<<ss<<endl;
            // Swap Frame Buffer in double buffering
            glEnable(GL_BLEND);
            RenderText(shader, ss, 25.0f, 540.0f, 0.30f, glm::vec3(0.5, 0.8f, 0.2f));
           // RenderText(shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
            glDisable(GL_BLEND);
            glfwSwapBuffers(window);
            //usleep(400000);
            
            tick_elements();
          //  tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

