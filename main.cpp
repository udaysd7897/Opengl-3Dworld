#include "main.h"
#include "timer.h"
#include "boat.h"
#include "ocean.h"
#include "monster.h"
#include "ball.h"
#include "boss.h"
#include "man.h"
#include "sail.h"
#include "island.h"
#include "bullet.h"
#include "reward.h"

#include <cstdlib>
#include <vector>
#include <math.h>
#include <unistd.h>


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int jf=0,bview=0,cview=1,tview=0,uview=0,hview=0,i=0,bf=0,dr=1,score=100;
int wind=0;
/**************************
* Customizable functions *
**************************/

Boat boat;
Man man;
Island island;
Boss boss;
Ocean ocean;
Sail sail;
Bullet bullet;
vector <Monster> monster;
vector <Ball> ball;
vector <Reward> reward;

float helix=0;
float heliz=0;
float heliheight=10;
float recx=1000;
float recz=1000;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0,rec_angle=0;
float camera_rotation_angle = 0,heliangle=0;
float offset=0;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void setview(int b,int c,int t,int u,int h)
{
    bview=b;
    cview=c;
    tview=t;
    uview=u;
    hview=h;
}
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
   // glm::vec3 eye ( 0, 10+boat.position.y, 10+boat.position.z);
    //glm::vec3 eye ( 5, 0, 0);
    //glm::vec3 eye ( 0, 10, 0);
    //glm::vec3 eye;
     if(uview){
        glm::vec3 eye ( boat.position.x, 10, boat.position.z);
        glm::vec3 target (boat.position.x, boat.position.y-offset, boat.position.z);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    if(tview){
        glm::vec3 eye ( 0, 10, 10);
        glm::vec3 target (boat.position.x, boat.position.y-offset, boat.position.z);
        glm::vec3 up (0, 0, 1);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    if(bview){
        glm::vec3 eye (boat.position.x-(1*sin(boat.rotation*M_PI/180)), boat.position.y+2, boat.position.z-(1*cos(boat.rotation*M_PI/180)));    //glm::vec3 eye ( 0,5*cos(camera_rotation_angle*M_PI/180.0f)+boat.position.y, 5*sin(camera_rotation_angle*M_PI/180.0f) );
        glm::vec3 target (boat.position.x+(1*sin(boat.rotation*M_PI/180)), boat.position.y-offset, boat.position.z+(1*cos(boat.rotation*M_PI/180)));
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }

    if(cview){
        //////printf("%f\n",offset);
        glm::vec3 eye ((boat.position.x-(5*sin(boat.rotation*M_PI/180))), 6, (boat.position.z-(5*cos(boat.rotation*M_PI/180))) );    //glm::vec3 eye ( 0,5*cos(camera_rotation_angle*M_PI/180.0f)+boat.position.y, 5*sin(camera_rotation_angle*M_PI/180.0f) );
        glm::vec3 target (boat.position.x, boat.position.y-offset, boat.position.z+2);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    if(hview)
    {
        glm::vec3 eye ( boat.position.x-1 -helix, heliheight , boat.position.z -1- heliz);
        glm::vec3 target ( boat.position.x, 1.0f, boat.position.z);
        glm::vec3 up (0, 1, 0);
        Matrices.view = glm::lookAt( eye, target, up );
    }
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    //glm::vec3 up (0, 0, 1);

    // Compute Camera matrix (view)
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    //cannon.draw(VP);
    for(i=0;i<100;i++){
        ball[i].draw(VP);
    }
    for(i=0;i<monster.size();i++){
        monster[i].draw(VP);
    }
    for(i=0;i<reward.size();i++){
        reward[i].draw(VP);
    }
    if(dr)
        boss.draw(VP);
    bullet.draw(VP);
    ocean.draw(VP);
    sail.draw(VP);
    boat.draw(VP);
    man.draw(VP);
    island.draw(VP);
}
int rock_collision()
{
    if(boat.position.y<=.15){
        for(i=0;i<100;i++){
            if(abs(boat.position.x-ball[i].position.x)<=(.25+.2)+abs(.5*sin(boat.rotation*M_PI/180)) )
                if(abs(boat.position.z-ball[i].position.z)<=(.5+.2)+abs(.5*cos(boat.rotation*M_PI/180)) )
                {
                    score-=5;
                    if(boat.position.x<ball[i].position.x){
                        boat.position.x-=.25;
                        sail.position.x-=.25;
                        boat.position.z-=.5;
                        sail.position.z-=.5;
                    }
                    else{ 
                        boat.position.x+=.25;
                        sail.position.x+=.25;
                        boat.position.z+=.5;
                        sail.position.z+=.5;
                    }
                    if(boat.position.z<ball[i].position.z){
                        boat.position.x-=.25;
                        sail.position.x-=.25;
                        boat.position.z-=.5;
                        sail.position.z-=.5;
                    }
                    else{ 
                        boat.position.x+=.25;
                        sail.position.x+=.25;
                        boat.position.z+=.5;
                        sail.position.z+=.5;
                    }
                    return 1;
                }
        }
    }
    return 0;
}
int mon_collision()
{
    for(i=0;i<10;i++){
        if(abs(boat.position.x-monster[i].position.x) <= (abs(.5*cos(boat.rotation*M_PI/180))+ monster[i].radius+ abs(2.2*sin(boat.rotation*M_PI/180))) )
        {
            if(abs(boat.position.z-monster[i].position.z)<=( abs(.5*sin(boat.rotation*M_PI/180))+monster[i].radius+ abs(2.2*cos(boat.rotation*M_PI/180))) )
            {
                score-=10;
                if(boat.position.x<monster[i].position.x){
                    boat.position.x-=monster[i].radius;
                    sail.position.x-=monster[i].radius;
                    boat.position.z-=monster[i].radius;
                    sail.position.z-=monster[i].radius;
                }
                else{ 
                    boat.position.x+=monster[i].radius;
                    sail.position.x+=monster[i].radius;
                    boat.position.z+=monster[i].radius;
                    sail.position.z+=monster[i].radius;
                }
                if(boat.position.z<monster[i].position.z){
                    boat.position.x-=monster[i].radius;
                    sail.position.x-=monster[i].radius;
                    boat.position.z-=monster[i].radius;
                    sail.position.z-=monster[i].radius;
                }
                else{ 
                    boat.position.x+=monster[i].radius;
                    sail.position.x+=monster[i].radius;
                    boat.position.z+=monster[i].radius;
                    sail.position.z+=monster[i].radius;
                }
                return 1;
            }
        }
    }
    return 0;
}
void scroll(GLFWwindow* window, double xpos, double ypos){
    float x,y;
    if(hview==1)
    {    
        if(recx == 1000.0 && recz == 1000.0 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
            recz = ypos;
            recx = xpos;
        }
        else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
            x = (float)(xpos-recx);
            y = (float)(ypos-recz);
            helix += x;
            heliz += y;
            recx = xpos;
            recz = ypos;
        }
        
    }
}
void bullet_collision()
{
    for(i=0;i<monster.size();i++){
        if( abs (bullet.position.x-monster[i].position.x) <= (monster[i].radius + .15))
            if(abs(bullet.position.z-monster[i].position.z)<=(.15 +monster[i].radius)) {
                float tx=monster[i].position.x;
                float tz=monster[i].position.z;
                monster.erase(monster.begin() +i);
               // printf(" re %d ",reward.size() );
                Reward  temp;
                temp       = Reward(tx, tz);
                reward.push_back(temp);
               // printf("%d\n",reward.size() );
            }
    }
}
void bull_boss_collision()
{
    if( abs (bullet.position.x-boss.position.x) <= (1.5 + .15))
        if(abs(bullet.position.z-boss.position.z)<=(.15 +1.5)) {
            float tx=boss.position.x;
            float tz=boss.position.z;
            dr=0;
            Reward  temp;
            temp       = Reward(tx, tz);
            reward.push_back(temp);
        }
}
void detect_reward()
{
    for(i=0;i<reward.size();i++){
        if( abs (boat.position.x-reward[i].position.x) <= .6)
            if(abs(boat.position.z-reward[i].position.z)<=.6) {
                score+=10;
                reward.erase(reward.begin() +i);
            }
    }
}
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int u = glfwGetKey(window, GLFW_KEY_U);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int h = glfwGetKey(window, GLFW_KEY_H);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    offset=0;
    if(hview)
        if(a)
            heliangle-=1;
        else if(d)
            heliangle+=1;
    if(x && bf==0)
    {
        //printf("aaaaa" );
        bullet.position.x=boat.position.x + 2.5*(sin(boat.rotation*M_PI/180));
        bullet.position.z=boat.position.z + 2.5*(cos(boat.rotation*M_PI/180));
        bullet.position.y=boat.position.y + .8;
        bf=1;
        rec_angle=boat.rotation;
        //bullet.draw();
        ////printf("%f %f %f %f\n",bullet.position.x,bullet.position.y,bullet.position.z,rec_angle);
    }
    if(b)
        setview(b,c,t,u,h);
    else if(c)
        setview(b,c,t,u,h);
    else if(t)
        setview(b,c,t,u,h);
    else if(u)
        setview(b,c,t,u,h);
    else if(h)
        setview(b,c,t,u,h);
    if (left) {
        sail.rotation=boat.rotation;
        boat.turn_left();
        man.turn_left();
        sail.turn_left();
    }
    if (right) {
        sail.rotation=boat.rotation;
        boat.turn_right();
        man.turn_right();
        sail.turn_right();
    }
    if(up){
        boat.position.z+= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        boat.position.x+= (0.1*sin(boat.rotation*M_PI/180));
        sail.position.z+= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        sail.position.x+= (0.1*sin(boat.rotation*M_PI/180));
        man.position.z+= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        man.position.x+= (0.1*sin(boat.rotation*M_PI/180));
        offset=boat.osc();
    }
    if(down){
        boat.position.z-= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        boat.position.x-= (0.1*sin(boat.rotation*M_PI/180));
        sail.position.z-= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        sail.position.x-= (0.1*sin(boat.rotation*M_PI/180));
        man.position.z-= /*abs*/(0.1*cos(boat.rotation*M_PI/180));
        man.position.x-= (0.1*sin(boat.rotation*M_PI/180));
        offset=boat.osc();
    }
    if(space && jf==0){
        jf=1;
    }

}
void wind_effect(int angle) {
        ////printf("agaya   %d\n",angle );
        boat.position.z+= /*abs*/(0.05*cos(boat.rotation*M_PI/180));
        boat.position.x+= (0.05*sin(boat.rotation*M_PI/180));
        sail.position.z+= /*abs*/(0.05*cos(boat.rotation*M_PI/180));
        sail.position.x+= (0.05*sin(boat.rotation*M_PI/180));
        man.position.z+= /*abs*/(0.05*cos(boat.rotation*M_PI/180));
        man.position.x+= (0.05*sin(boat.rotation*M_PI/180));
        sail.rotation=-40;
        offset=boat.osc();
}
void tick_elements() {
    char buffer[100];
    sprintf(buffer,"Zelda          HEALTH: %d",score);  
    glfwSetWindowTitle(window,buffer);
    wind++;
    int win_angle=(int)boat.rotation%360;
    ////printf("%d %d\n",wind,win_angle);
    if(wind==360)
		wind=1;
    //sail.rotation=0;
    if(wind<=90)
        if(win_angle<=10)
            wind_effect(win_angle);
    if( wind>90 && wind <=180)
        if(win_angle<=95 && win_angle>=85)
            wind_effect(win_angle);
    if(wind<=270 && wind>180)
        if(win_angle<=185 && win_angle>=175)
            wind_effect(win_angle);
    if(wind<=360 && wind>270)
        if(win_angle<=275 && win_angle>=265)
            wind_effect(win_angle);
    if(jf)
    {
        boat.jump(&jf);
        man.jump(&jf);
    }
    if(bf){
        bullet.shoot(&bf,rec_angle);
        bullet_collision();
        bull_boss_collision();
    }
    if(monster.size()<=4)
    {
        boss.position.x=2;
        boss.position.z=2;
    }
    rock_collision();
    mon_collision();
    detect_reward();
    for(i=0;i<monster.size();i++){
        monster[i].tick();
    }
    boss.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    for( i=0;i<100;i++){
        int x=rand() % 150 + 1; 
        int y=rand() % 150 + 1;
        int sx=rand() %  4; 
        int sy=rand() %  4;
        if((sx%2)==0){
            x*=-1;
        }
        if((sy%2)==0){
            y*=-1;
        }
        //////printf("%d %d\n",x,y);
        Ball  temp;
        temp       = Ball(x, y, COLOR_GRAY);
        ball.push_back(temp);
    }
    for( i=0;i<10;i++){
        int x=rand() % 50 + 1; 
        int y=rand() % 50 + 1;
        int sx=rand() %  4; 
        int sy=rand() %  4;
        if((sx%2)==0){
            x*=-1;
        }
        if((sy%2)==0){
            y*=-1;
        }
        int r=rand() % 2 + 1; 
        //////printf("%d %d\n",x,y);
        Monster  temp;
        temp       = Monster(x, y, (float)r, i);
        monster.push_back(temp);
    }
    for( i=0;i<5;i++)
    {

        int x=rand() % 50 + 1; 
        int y=rand() % 50 + 1;
        int sx=rand() %  4; 
        int sy=rand() %  4;
        if((sx%2)==0){
            x*=-1;
        }
        if((sy%2)==0){
            y*=-1;
        }
        int r=rand() % 2 + 1; 
        Reward  temp;
        temp       = Reward(x, y);
        reward.push_back(temp);
    }
    bullet     = Bullet(boat.position.x, 1000);
    ocean      = Ocean(0, 0, COLOR_BLUE);
    sail       = Sail(0, 0, COLOR_WHITE);
    boat       = Boat(0, 0, COLOR_YELLOW);
    boss       = Boss(2, 1000);
    man        = Man(0, .7);
    island     = Island(80, 80,     COLOR_GREEN);

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

   // printf("%f %f\n",boat.position.x,boat.position.z );
    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

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
            glfwSetCursorPosCallback(window, scroll);
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
    //Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(1.57f, 1.0f, 1.0f,  500.0f);
}
