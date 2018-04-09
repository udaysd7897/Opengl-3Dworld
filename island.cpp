#include "island.h"
#include "main.h"

Island::Island(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    //speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -10,0.2,-10.0f, // triangle 1 : begin
        10,0.2, 10.0f,
        10,0.2, -10.0f,
         // triangle 1 : end
        10,0.2, 10, // triangle 1 : end
        -10,0.2,-10, // triangle 1 : begin
        -10,0.2, 10,

    };
    this->object = create3DObject(GL_TRIANGLES, 2*3,vertex_buffer_data, COLOR_GREEN, GL_FILL);
    
    static const GLfloat vertex_buffer_tree[] = {
        3,6.2,3,
        -3,6.2,-3,
        -3,6.2,3,

        3,6.2,3,
        -3,6.2,-3,
        3,6.2,-3,

        -3,6.2,-3,
        3,6.2,-3,
        0,10.2,0,
        
        3,6.2,3,
        3,6.2,-3,
        0,10.2,0,

        -3,6.2,-3,
        -3,6.2,3,
        0,10.2,0,
        
        3,6.2,3,
        -3,6.2,3,
        0,10.2,0,
    
    };

    this->tree = create3DObject(GL_TRIANGLES, 6*3,vertex_buffer_tree, COLOR_LGREEN, GL_FILL);
    float angle=0,step=1,radius=.8;
    int ind=0;
    GLfloat vertex_buffer_pole[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float zi = radius * sin(theta);

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=6.5;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=0;

        angle=angle+step;
    };
    this->pole = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_pole, COLOR_BROWN, GL_FILL);
    
}
void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->tree);
    draw3DObject(this->pole);
}

void Island::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Island::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

