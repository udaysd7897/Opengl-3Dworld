#include "monster.h"
#include "main.h"

#include <cstdlib>
#include <math.h>
#include <unistd.h>

int ti=0;
Monster::Monster(float x, float y,float r,int ind) {
    this->position = glm::vec3(x, 1.5, y  );
    this->rotation = 0;
    this->index = ind;
    speed = .04;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    float i,j;

    GLfloat vertex_buffer_data[1200000];
     
     int k=0;
     this->radius=r;
     float pi = M_PI/180.0f;
     for(i=-90;i<=90;i+=1)
     {
        for(j=0;j<360;j+=1)
        {
            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i);
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*(i+1));
            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i);
            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*(i+1));
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i);
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*(i));
            vertex_buffer_data[k++] = r*sin(pi*(i+1));
            
        }

     }
    for(i=0;i<20;i++)
    {
        int alpha=rand() %360;
        int beta=rand() %180;

        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=r/5;   
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha);
        vertex_buffer_data[k++]=2*r*cos(beta);
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha);
        vertex_buffer_data[k++]=2*r*cos(beta);
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha);
        vertex_buffer_data[k++]=2*r*cos(beta);
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);

        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=-r/5;
        vertex_buffer_data[k++]=0;
        vertex_buffer_data[k++]=r/5;
        vertex_buffer_data[k++]=2*r*sin(beta)*cos(alpha);
        vertex_buffer_data[k++]=2*r*cos(beta);
        vertex_buffer_data[k++]=2*r*sin(beta)*sin(alpha);
    }
   // printf("%d\n",k);
    if((ind%2)==0)
        this->object = create3DObject(GL_TRIANGLES, 181*360*2*3+20*4*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    else 
        this->object = create3DObject(GL_TRIANGLES, 181*360*2*3+20*4*3, vertex_buffer_data, COLOR_VIOLET, GL_FILL);
     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Monster::set_position(float x, float y) {
    this->position = glm::vec3(x, 1.5, y  );
}

void Monster::tick() {
    this->rotation+=1;
    ti++;
    ti=ti%600;
    //printf("%d\n",ti);
    if(ti==0)
        speed*=-1;
    this->position.x+=speed*(this->index%2);
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
