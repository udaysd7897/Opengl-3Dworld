#include "man.h"
#include "main.h"

#include <cstdlib>
#include <math.h>
#include <unistd.h>


Man::Man(float x, float y) {
    this->position = glm::vec3(x, 0, y  );
    this->rotation = 0;
    speed = 1.2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.

     
    float angle=0,step=1,radius=.35;
    int ind=0;
    GLfloat vertex_buffer_pole[360*9];
    while(angle<360)
    {
        float theta=(angle*M_PI)/180;
        float xi = radius * cos(theta);
        float zi = radius * sin(theta);

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=1.5;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=xi;
        vertex_buffer_pole[ind++]=.6;
        vertex_buffer_pole[ind++]=zi;

        vertex_buffer_pole[ind++]=0;
        vertex_buffer_pole[ind++]=.6;
        vertex_buffer_pole[ind++]=0;

        angle=angle+step;
    };
    this->pole = create3DObject(GL_TRIANGLES, 360*3,vertex_buffer_pole, COLOR_LGREEN, GL_FILL);
    GLfloat vertex_buffer_data[600000];
    int k=0,i,j;
    float pi = M_PI/180.0f,r=.3;
    for(i=-90;i<=90;i+=1)
    {
        for(j=0;j<360;j+=1)
        {
            vertex_buffer_data[k++] = r*cos(pi*j)*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i)+1.8;
            vertex_buffer_data[k++] = r*sin(pi*j)*cos(pi*i);

            vertex_buffer_data[k++] = r*cos(pi*(j+1))*cos(pi*i);
            vertex_buffer_data[k++] = r*sin(pi*i)+1.8;
            vertex_buffer_data[k++] = r*sin(pi*(j+1))*cos(pi*i);
            
            vertex_buffer_data[k++] = 0;
            vertex_buffer_data[k++] = 1.8;
            vertex_buffer_data[k++] = 0;
        }
    }
    this->sphere = create3DObject(GL_TRIANGLES, 181*360*3, vertex_buffer_data, COLOR_SKIN, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 181*360*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);     // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_limb[]={
    };
    this->limbs = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_limb, COLOR_SKIN, GL_FILL);

}

void Man::draw(glm::mat4 VP) {
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
    draw3DObject(this->limbs);
}

void Man::turn_right(){
    this->rotation -=1;
}
void Man::turn_left(){
    this->rotation +=1;
}
void Man::jump(int *flag){
    this->position.y += speed;
    speed=-.02;
    if(this->position.y<=0.1 && this->position.y>=-.1)
    {
        this->position.y=0;
        speed=1.2;
        *flag=0;
    }
}
void Man::set_position(float x, float y) {
//    this->position::vec3(x, 0, y  );
}

