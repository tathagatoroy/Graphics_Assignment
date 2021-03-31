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



using namespace std;

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
Power obstacles[10];
Power health[10];
int object = -1;



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

/*test code to see how it works 
float traingle[] = { 
    0.0f,0.0f,
    1.0f,1.0f,
    -1.0f,-1.0f

};

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
    hero.draw(VP);
    //cout<<villain.alive<<endl;
  
    //  cout<<"DRAWING VILLAIN"<<endl;
    villain.draw(VP);
    
    
    ball1.draw(VP);
    for(int i=0;i<10;i++){
        health[i].draw(VP);
        obstacles[i].draw(VP);
    }
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
}
   


void tick_elements() {


    //ball1.tick();
int cur_x = (int)hero.position.x;
int cur_y  = (int)hero.position.y;
int button_x = (int)ball1.position.x;
int button_y = (int)ball1.position.y;
int pow_x = (int)ball2.position.x;
int pow_y = (int)ball2.position.y;
//check you can kill the villain
if(cur_x == button_x && button_y == cur_y)
{
    villain.kill();
    ball1.eaten();
}
//check you can activate powerups
if(cur_x == pow_x && cur_y == pow_y){
    ball2.eaten();
    for(int i=0;i<10;i++){
        health[i].activate();
        obstacles[i].activate();
    }
}
//checking whether gained some powerups
for(int i = 0;i<10;i++)
{
    int h_x = (int)health[i].position.x;
    int h_y = (int)health[i].position.y;
    if(cur_x == h_x && cur_y == h_y)
    {
        health[i].eaten();
        hero.reduce_health(health[i].score);

    }

}
for(int i = 0;i<10;i++)
{
    int h_x = (int)obstacles[i].position.x;
    int h_y = (int)obstacles[i].position.y;
    if(cur_x == h_x && cur_y == h_y)
    {
        obstacles[i].eaten();
        hero.reduce_health(obstacles[i].score);

    }

}
{
    int h1_x = 
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

    villain.tick(dir);
}


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(13.50, 18.50, COLOR_GREEN);
    ball2       = Ball(4.50,2.50,COLOR_THREE)

    second    = Maze(0, 0, COLOR_RED);
    first         = Shape1(0,0,COLOR_RED);
    third       = Shape3(0,0, COLOR_RED);
    hero       = Player(5.50,5.50,COLOR_RED);
    villain    = Imposter(13.50,11.50,COLOR_RED);
    for(int i = 0;i < 10; i++ )
    {
        int num = rand() % 400;//height *width;
        int y = rand() / 20;
        float y1 = (float)y + 0.50;
        int x = rand() % 20;
        float x1 = (float)x + 0.50;
        int num1 = rand() % 400;
        int a = rand() / 20;
        float a1 = (float)a + 0.50;
        int b = rand() % 20;
        float b1 = (float)b + 0.50;
        health[i] = Powerups(x1,y1,10,COLOR_TWO);
        obstacles[i] = Powerups(b1,a1,-10,COLOR_ONE)

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
   
    srand(time(0));
    int width  = 600;
    int height = 600;
 
    //creates the window 
    window = initGLFW(width, height);

    initGL (window, width, height);
    glfwSetKeyCallback(window, key_callback);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            usleep(400000);
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
