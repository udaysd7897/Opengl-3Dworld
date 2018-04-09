#include "boat.h"
#include "main.h"
#include <math.h>

Boat::Boat(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1.2;
    osc_speed = 0.2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_sides[] = {
         -0.25,0,-1.0f, // triangle 1 : begin
         -0.25,0, 1.0f, // triangle 1 : begin
         -0.45,0.6, -1.0f, // triangle 1 : begin
            
         -0.25,0, 1.0f, // triangle 1 : begin
         -0.45,0.6, -1.0f, // triangle 1 : begin
         -0.45,0.6, 1.0f, // triangle 1 : begin

         0.25,0,-1.0f, // triangle 1 : begin
         0.25,0, 1.0f, // triangle 1 : begin
         0.45,0.6, -1.0f, // triangle 1 : begin
            
         0.25,0, 1.0f, // triangle 1 : begin
         0.45,0.6, -1.0f, // triangle 1 : begin
         0.45,0.6, 1.0f, // triangle 1 : begin

         0.25,0, 1.0f, // triangle 1 : begin
         0,0, 1.5f, // triangle 1 : begin
         0,0.8, 1.8f, // triangle 1 : begin

         0,0.8, 1.8f, // triangle 1 : begin
         0.25,0, 1.0f, // triangle 1 : begin
         0.45,0.6, 1.0f, // triangle 1 : begin

         -0.25,0, 1.0f, // triangle 1 : begin
         0,0, 1.5f, // triangle 1 : begin
         0,0.8, 1.8f, // triangle 1 : begin

         0,0.8, 1.8f, // triangle 1 : begin
         -0.25,0, 1.0f, // triangle 1 : begin
         -0.45,0.6, 1.0f, // triangle 1 : begin

         //  0.25,0,-1.0f, // triangle 1 : begin
         0.25,0, -1.0f, // triangle 1 : begin
         0,0, -1.5f, // triangle 1 : begin
         0,0.8, -1.8f, // triangle 1 : begin

         0,0.8, -1.8f, // triangle 1 : begin
         0.25,0, -1.0f, // triangle 1 : begin
         0.45,0.6, -1.0f, // triangle 1 : begin

         -0.25,0, -1.0f, // triangle 1 : begin
         0,0, -1.5f, // triangle 1 : begin
         0,0.8, -1.8f, // triangle 1 : begin

         0,0.8, -1.8f, // triangle 1 : begin
         -0.25,0, -1.0f, // triangle 1 : begin
         -0.45,0.6, -1.0f, // triangle 1 : begin
    };

    this->sides = create3DObject(GL_TRIANGLES, 12*3,vertex_buffer_sides, COLOR_YELLOW, GL_FILL);
    
    static const GLfloat vertex_buffer_base[] = {
        -0.25,0,-1.0f, // triangle 1 : begin
        0.25,0, 1.0f,
        0.25,0, -1.0f,
         // triangle 1 : end
        -0.25,0,-1.0f, // triangle 1 : begin
        -0.25,0, 1.0f,
        0.25,0, 1.0f, // triangle 1 : end

        0.25,0, 1.0f, // triangle 1 : end
        -0.25,0, 1.0f,
        0 ,0, 1.5f, // triangle 1 : en

        0.25,0, -1.0f, // triangle 1 : end
        -0.25,0, -1.0f,
        0 ,0, -1.5f, // triangle 1 : en
    };
    this->base = create3DObject(GL_TRIANGLES, 4*3,vertex_buffer_base, COLOR_RED, GL_FILL);

    float angle=0,step=1,radius=0.15;
    int ind=0;
    GLfloat vertex_buffer_cannon[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float yi = radius * sin(theta)+0.7;

        vertex_buffer_cannon[ind++]=xi;
        vertex_buffer_cannon[ind++]=yi+.5;
        vertex_buffer_cannon[ind++]=1.2+1.4;

        vertex_buffer_cannon[ind++]=xi;
        vertex_buffer_cannon[ind++]=yi;
        vertex_buffer_cannon[ind++]=1.4;

        vertex_buffer_cannon[ind++]=0;
        vertex_buffer_cannon[ind++]=0.7;
        vertex_buffer_cannon[ind++]=1.4;

        angle=angle+step;
    };
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->cannon = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_cannon, COLOR_BLACK, GL_FILL);
    
    angle=0,step=1,radius=0.02;
    ind=0;
    GLfloat vertex_buffer_pole[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float zi = radius * sin(theta);

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=2.5;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=0;

        angle=angle+step;
    };
    this->pole = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_pole, COLOR_LGREEN, GL_FILL);
}


void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->sides);
    draw3DObject(this->base);
    draw3DObject(this->cannon);
    draw3DObject(this->pole);
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Boat::turn_right(){
    this->rotation -=1;
}
void Boat::turn_left(){
    this->rotation +=1;
}
void Boat::jump(int *flag){
    this->position.y += speed;
    speed=-.02;
    if(this->position.y<=0.1 && this->position.y>=-.1)
    {
        this->position.y=0;
        speed=1.2;
        *flag=0;
    }
}
float Boat::osc( ){
    this->position.y += osc_speed;
    float temp=this->position.y;
    osc_speed=-.005;
    if(this->position.y<=0.1 && this->position.y>=-.1)
    {
        this->position.y=0;
        osc_speed=0.2;
    }
    return temp;
}
void Boat::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

