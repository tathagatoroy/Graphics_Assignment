#include "main.h"
#include "timer.h"
#include "ball.h"
#include "shape1.h"
#include "shape2.h"
#include "shape3.h"
#include "glm/ext.hpp"


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Shape1 first;
Shape2 second;
Shape3 third;
int object = -1;



float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float camera_x = 5*cos(camera_rotation_angle*M_PI/180.0f);
float camera_y = 0;
float camera_z = 5*sin(camera_rotation_angle*M_PI/180.0f);
float target_x = camera_x-5*cos(camera_rotation_angle*M_PI/180.0f);
float target_y = camera_y;
float target_z = camera_z;
float rotate = 0;


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
    if(object == 1)
    first.draw(VP);
    else if(object == 2)
    second.draw(VP);
    else
    third.draw(VP);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{//move objects
cout<<"object "<<object<<endl;
if(object == 3)
{
   if(key == GLFW_KEY_A && action == GLFW_PRESS)
   third.up();
   else if(key == GLFW_KEY_B && action == GLFW_PRESS)
   third.down();
   else if(key == GLFW_KEY_C && action == GLFW_PRESS)
   third.right();
   else if(key == GLFW_KEY_D && action == GLFW_PRESS)
   third.left();
   else if(key == GLFW_KEY_E && action == GLFW_PRESS)
   third.front();
   else if(key == GLFW_KEY_F && action == GLFW_PRESS)
   third.back();
   //move camera 
   else if(key == GLFW_KEY_G && action == GLFW_PRESS)
   {
       camera_x += 1;
       target_x += 1;
   }
   else if(key == GLFW_KEY_H && action == GLFW_PRESS)
   {
       camera_x -= 1;
       target_x -= 1;
   }
   else if(key == GLFW_KEY_I && action == GLFW_PRESS)
   {
       camera_y += 1;
       target_y += 1;
   }
   else if(key == GLFW_KEY_J && action == GLFW_PRESS)
   {
       camera_y -= 1;
       target_y -= 1;
   }
   else if(key == GLFW_KEY_K && action == GLFW_PRESS)
   {
       camera_z += 1;
       target_z += 1;
   }
   else if(key == GLFW_KEY_L && action == GLFW_PRESS)
   {
       camera_z -= 1;
       target_z -= 1;
   }
   //teleport to the (0,0,0)
   else if(key == GLFW_KEY_M && action == GLFW_PRESS)
   {
       camera_x = 5;
       camera_y = 0;
       camera_z = 0;
       target_x = third.position.x;
       target_y = third.position.y;
       target_z = third.position.z;
   }
   //teleport to top (0,0,5)
   else if(key == GLFW_KEY_N && action == GLFW_PRESS)
   {
       camera_y = 0;
       camera_x = 0;
       camera_z = 5;
       target_x = third.position.x;
       target_y = third.position.y;
       target_z = third.position.z;
       /*cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
   */}
   
   //teleport to the (3,3,3)
   else if(key == GLFW_KEY_O && action == GLFW_PRESS)
   {
       camera_y = 3;
       camera_x = 3;
       camera_z = 3;
       target_x = third.position.x;
       target_y = third.position.y;
       target_z = third.position.z;
      /* cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
  */ }
  //rotate about y axis
  else if(key == GLFW_KEY_P && action == GLFW_PRESS)
  {
      third.rotate();
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS)
  {
    if(rotate == 0)
    {
        cout<<"rotate"<<endl;
        third.set_position(0.0f,0.0f);
        //recentering
        camera_x = 5;
        camera_y = 0;
        camera_z = 0;
        target_x = 0;
        target_y = 0;
        target_z = 0;
        rotate = 1;
    }
    else rotate = 0;
    
  }
}
else if(object == 2)
{
    cout<<"object 2"<<endl;
    if(key == GLFW_KEY_A && action == GLFW_PRESS)
   second.up();
   else if(key == GLFW_KEY_B && action == GLFW_PRESS)
   second.down();
   else if(key == GLFW_KEY_C && action == GLFW_PRESS)
   second.right();
   else if(key == GLFW_KEY_D && action == GLFW_PRESS)
   second.left();
   else if(key == GLFW_KEY_E && action == GLFW_PRESS)
   second.front();
   else if(key == GLFW_KEY_F && action == GLFW_PRESS)
   second.back();
   //move camera 
   else if(key == GLFW_KEY_G && action == GLFW_PRESS)
   {
       camera_x += 1;
       target_x += 1;
   }
   else if(key == GLFW_KEY_H && action == GLFW_PRESS)
   {
       camera_x -= 1;
       target_x -= 1;
   }
   else if(key == GLFW_KEY_I && action == GLFW_PRESS)
   {
       camera_y += 1;
       target_y += 1;
   }
   else if(key == GLFW_KEY_J && action == GLFW_PRESS)
   {
       camera_y -= 1;
       target_y -= 1;
   }
   else if(key == GLFW_KEY_K && action == GLFW_PRESS)
   {
       camera_z += 1;
       target_z += 1;
   }
   else if(key == GLFW_KEY_L && action == GLFW_PRESS)
   {
       camera_z -= 1;
       target_z -= 1;
   }
   //teleport to the (0,0,0)
   else if(key == GLFW_KEY_M && action == GLFW_PRESS)
   {
       camera_x = 5;
       camera_y = 0;
       camera_z = 0;
       target_x = second.position.x;
       target_y = second.position.y;
       target_z = second.position.z;
   }
   //teleport to top (0,0,5)
   else if(key == GLFW_KEY_N && action == GLFW_PRESS)
   {
       camera_y = 0;
       camera_x = 0;
       camera_z = 5;
       target_x = second.position.x;
       target_y = second.position.y;
       target_z = second.position.z;
       /*cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
   */}
   
   //teleport to the (3,3,3)
   else if(key == GLFW_KEY_O && action == GLFW_PRESS)
   {
       camera_y = 3;
       camera_x = 3;
       camera_z = 3;
       target_x = second.position.x;
       target_y = second.position.y;
       target_z = second.position.z;
      /* cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
  */ }
  //rotate about y axis
  else if(key == GLFW_KEY_P && action == GLFW_PRESS)
  {
      second.rotate();
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS)
  {
    if(rotate == 0)
    {
        cout<<"rotate"<<endl;
        second.set_position(0.0f,0.0f);
        //recentering
        camera_x = 5;
        camera_y = 0;
        camera_z = 0;
        target_x = 0;
        target_y = 0;
        target_z = 0;
        rotate = 1;
    }
    else rotate = 0;
    
  }
}
else if(object == 1)
{
    if(key == GLFW_KEY_A && action == GLFW_PRESS)
   first.up();
   else if(key == GLFW_KEY_B && action == GLFW_PRESS)
   first.down();
   else if(key == GLFW_KEY_C && action == GLFW_PRESS)
   first.right();
   else if(key == GLFW_KEY_D && action == GLFW_PRESS)
   first.left();
   else if(key == GLFW_KEY_E && action == GLFW_PRESS)
   first.front();
   else if(key == GLFW_KEY_F && action == GLFW_PRESS)
   first.back();
   //move camera 
   else if(key == GLFW_KEY_G && action == GLFW_PRESS)
   {
       camera_x += 1;
       target_x += 1;
   }
   else if(key == GLFW_KEY_H && action == GLFW_PRESS)
   {
       camera_x -= 1;
       target_x -= 1;
   }
   else if(key == GLFW_KEY_I && action == GLFW_PRESS)
   {
       camera_y += 1;
       target_y += 1;
   }
   else if(key == GLFW_KEY_J && action == GLFW_PRESS)
   {
       camera_y -= 1;
       target_y -= 1;
   }
   else if(key == GLFW_KEY_K && action == GLFW_PRESS)
   {
       camera_z += 1;
       target_z += 1;
   }
   else if(key == GLFW_KEY_L && action == GLFW_PRESS)
   {
       camera_z -= 1;
       target_z -= 1;
   }
   //teleport to the (0,0,0)
   else if(key == GLFW_KEY_M && action == GLFW_PRESS)
   {
       camera_x = 5;
       camera_y = 0;
       camera_z = 0;
       target_x = first.position.x;
       target_y = first.position.y;
       target_z = first.position.z;
   }
   //teleport to top (0,0,5)
   else if(key == GLFW_KEY_N && action == GLFW_PRESS)
   {
       camera_y = 0;
       camera_x = 0;
       camera_z = 5;
       target_x = first.position.x;
       target_y = first.position.y;
       target_z = first.position.z;
       /*cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
   */}
   
   //teleport to the (3,3,3)
   else if(key == GLFW_KEY_O && action == GLFW_PRESS)
   {
       camera_y = 3;
       camera_x = 3;
       camera_z = 3;
       target_x = first.position.x;
       target_y = first.position.y;
       target_z = first.position.z;
      /* cout<<"camera position : "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
       cout<<"target position : "<<target_x<<" "<<target_y<<" "<<target_z<<endl;
       cout<<"object position : "<<third.position.x<<" "<<third.position.y<<" "<<third.position.y<<endl;
  */ }
  //rotate about x axis
  else if(key == GLFW_KEY_P && action == GLFW_PRESS)
  {
      first.rotate();
  }
  else if(key == GLFW_KEY_R && action == GLFW_PRESS)
  {
    if(rotate == 0)
    {
        cout<<"rotate"<<endl;
        first.set_position(0.0f,0.0f);
        //recentering
        camera_x = 5;
        camera_y = 0;
        camera_z = 0;
        target_x = 0;
        target_y = 0;
        target_z = 0;
        rotate = 1;
    }
    else rotate = 0;
    
  }
}

}


void tick_input(GLFWwindow *window) {
   /* int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up =   glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int front = glfwGetKey(window, GLFW_KEY_A);
    int back = glfwGetKey(window, GLFW_KEY_B);*/
    /*if (left == GLFW_PRESS) {
        third.left();
        cout<<"left"<<endl;
        // Do something
    }
    else if(right == GLFW_PRESS) {
        third.right();
        cout<<"right"<<endl;
    }
    else if(up == GLFW_PRESS) {
        third.up();
        cout<<"up"<<endl;
    }
    else if(down == GLFW_PRESS)
    {
        third.down();
        cout<<"down"<<endl;
    }
    else if(front == GLFW_PRESS)
    {
        third.front();
        cout<<"front"<<endl;
    }
    else if(back == GLFW_PRESS)
    {
        third.back();
        cout<<"back"<<endl;
    }*/
}

void tick_elements() {
    //ball1.tick();
    if(object == 3)
    third.tick();
    else if(object == 2)
    second.tick();
    else 
    first.tick();
    if(rotate  == 1)
    {
        camera_rotation_angle += 1;
        camera_x = 5*cos(camera_rotation_angle*M_PI/180.0f);
        camera_y = 0;
        camera_z = 5*sin(camera_rotation_angle*M_PI/180.0f);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_RED);
    first     = Shape1(0, 0, COLOR_RED);
    second         = Shape2(0,0,COLOR_RED);
    third       = Shape3(0,0, COLOR_RED);

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


int main(int argc, char **argv) {
    cout<<argc<<endl;
    for(int i=0;i<argc;i++)
    cout<<i<<" "<<argv[i]<<endl;
    if(argc !=  2)
    exit(1);
    else if(strcmp(argv[1],"1") == 0){
    object = 1;
    //cout<<"oho"<<endl;
    }
    else if(strcmp(argv[1],"2") == 0)
    {
        object =2;
    }

    else if(strcmp(argv[1],"3") == 0)
    object = 3;
    else 
    exit(1);
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

            tick_elements();
            tick_input(window);
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
