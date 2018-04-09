#include "bullet.h"
#include "main.h"

#include <cstdlib>
#include <math.h>
#include <unistd.h>


Bullet::Bullet(float x, float y) {
    this->position = glm::vec3(x, 1.5, y  );
    this->rotation = 0;
    speed = 0.4;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    float i,j;

    GLfloat vertex_buffer_data[600000];
     
    int k=0;
    float pi = M_PI/180.0f,r=.15;
    for(i=-90;i<=90;i+=1)
    {
        for(j=0;j<360;j+=1)
        {
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*i);

            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*i);
            
            vertex_buffer_data[k++] = 0;
            vertex_buffer_data[k++] = 0;
            vertex_buffer_data[k++] = 0;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, 181*360*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, .8, y  );
}
void Bullet::shoot(int *flag,float angle) {
    float alpha=(angle*M_PI)/180;
    if(this->position.y<.1){
        speed=0.4;
        this->position.y=1000;
        *flag=0;
    }
    this->position.x+=0.3*sin(alpha);
    this->position.z+=0.3*cos(alpha);
    this->position.y+=speed;
    speed-=0.02;
    //printf("%f %f %f\n",this->position.x,this->position.y,this->position.z );
}

