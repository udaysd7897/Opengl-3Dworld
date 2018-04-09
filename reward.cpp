#include "reward.h"
#include "main.h"

#include <cstdlib>
#include <math.h>
#include <unistd.h>


Reward::Reward(float x, float y) {
    this->position = glm::vec3(x, 0, y  );
    this->rotation = 0;
    speed = 2;
    float angle=0,step=1,radius=0.2;
    int ind=0;
    GLfloat vertex_buffer_cannon[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float yi = radius * sin(theta);

        vertex_buffer_cannon[ind++]=xi;
        vertex_buffer_cannon[ind++]=yi;
        vertex_buffer_cannon[ind++]=.6;

        vertex_buffer_cannon[ind++]=xi;
        vertex_buffer_cannon[ind++]=yi;
        vertex_buffer_cannon[ind++]=-.6;

        vertex_buffer_cannon[ind++]=0;
        vertex_buffer_cannon[ind++]=0;
        vertex_buffer_cannon[ind++]=0;

        angle=angle+step;
    };

    this->cannon = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_cannon, COLOR_BROWN, GL_FILL);

    static const GLfloat vertex_buffer_cis[] = {
        .1,.4,.1,
        .1,.4,-.1,
        0,.6,-0,

        -.1,.4,-.1,
        -.1,.4,.1,
        0,.6,-0
        ,
        .1,.4,.1,
        -.1,.4,.1,
        0,.2,-0,

        -.1,.4,-.1,
        .1,.4,-.1,
        0,.2,-0,
    };
    this->cis = create3DObject(GL_TRIANGLES, 4*3,vertex_buffer_cis, COLOR_PINK, GL_FILL);
    static const GLfloat vertex_buffer_trans[] = {
        .1,.4,.1,
        -.1,.4,.1,
        0,.6,-0,

        -.1,.4,-.1,
        .1,.4,-.1,
        0,.6,-0
        ,
        .1,.4,.1,
        .1,.4,-.1,
        0,.2,-0,

        -.1,.4,-.1,
        -.1,.4,.1,
        0,.2,-0,
    };
    this->trans = create3DObject(GL_TRIANGLES, 4*3,vertex_buffer_trans, COLOR_VIOLET, GL_FILL);
// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.

     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Reward::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon);
    draw3DObject(this->cis);
    draw3DObject(this->trans);
}

void Reward::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y  );
}

void Reward::tick() {
    this->rotation+=1;
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

