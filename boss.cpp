#include "boss.h"
#include "main.h"

#include <cstdlib>
#include <math.h>
#include <unistd.h>


Boss::Boss(float x, float y) {
    this->position = glm::vec3(x, 0, y  );
    this->rotation = 0;
    speed = 2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.

     
    float angle=0,step=1,radius=2;
    int ind=0;
    GLfloat vertex_buffer_pole[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float zi = radius * sin(theta);

        vertex_buffer_pole[ind++]=xi+6;
        vertex_buffer_pole[ind++]=3.5;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=xi+6;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=0+6;
        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=0;

        angle=angle+step;
    };
    this->pole = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_pole, COLOR_LGREEN, GL_FILL);
    GLfloat vertex_buffer_data[600000];
    int k=0,i,j;
    float pi = M_PI/180.0f,r=2;
    for(i=-90;i<=90;i+=1)
    {
        for(j=0;j<360;j+=1)
        {
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*i)+6;
            vertex_buffer_data[k++] = r*sin(pi*i)+4.2;
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*i);

            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*i)+6;
            vertex_buffer_data[k++] = r*sin(pi*i)+4.2;
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*i);
            
            vertex_buffer_data[k++] = 0+6;
            vertex_buffer_data[k++] = 4.2;
            vertex_buffer_data[k++] = 0;
        }
    } 
    for(i=0;i<5;i++)
    {
        int alpha=rand() %360;
        int beta=rand() %180;

        vertex_buffer_data[k++]=r/5+6;
        vertex_buffer_data[k++]=4.2;
        vertex_buffer_data[k++]=r/5;   
        vertex_buffer_data[k++]=r/5+6;
        vertex_buffer_data[k++]=4.2;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha)+6;
        vertex_buffer_data[k++]=2*r*cos(beta)+4.2;
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=-r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha)+6;
        vertex_buffer_data[k++]=2*r*cos(beta)+4.2;
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=-r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=-r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha)+6;
        vertex_buffer_data[k++]=2*r*cos(beta)+4.2;
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=-r/5+6;
        vertex_buffer_data[k++]=0+4.2;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha)+6;
        vertex_buffer_data[k++]=2*r*cos(beta)+4.2;
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);
    }
    this->sphere = create3DObject(GL_TRIANGLES, 181*360*3+20*4*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 181*360*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 3, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0))3
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //draw3DObject(this->object);
    draw3DObject(this->sphere);
    draw3DObject(this->pole);
}

void Boss::set_position(float x, float y) {
    this->position = glm::vec3(x, 1.5, y  );
}

void Boss::tick() {
    this->rotation+=2;
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
