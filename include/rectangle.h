#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <vector>
#include "shared.h"


class Rectangle
{
private:
    uint32_t vao, vbo , ebo;

    std::vector<uint32_t> indices;
    std::vector<float> vertices; 

public:
    float w , h, x , y;


    Rectangle();
    Rectangle(float x , float y  ,float w, float h);

    void setColor(float r, float g , float b);

    void render(Shader shader);
    
    void clean();
    ~Rectangle();
};

Rectangle::Rectangle() {}
Rectangle::Rectangle(float _x , float _y,float _w , float _h) {
    w = _w; h = _h;
    x = _x; y = _y;

    vertices = {
        x, y ,  0.f ,        1.f,1.f,1.f, 
        x + w, y  , 0.f ,    1.f,1.f,1.f, 
        x + w, y + h , 0.f , 1.f,1.f,1.f,
        x, y + h ,  0.f ,    1.f,1.f,1.f,
    };




    indices = {
        0, 1 ,2,
        0, 2 ,3,
    };

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_STATIC_DRAW);

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() *  sizeof(uint32_t),indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6 * sizeof(float),(void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void Rectangle::setColor(float r, float g , float b) {

    for(int i = 0 ; i < 4 ; i++) {
        vertices[6 * i + 3 + 0] = r;
        vertices[6 * i + 3 + 1] = g;
        vertices[6 * i + 3 + 2] = b;
    }

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_STATIC_DRAW);
}


void Rectangle::render(Shader shader) {
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);    
}
void Rectangle::clean() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDeleteBuffers(1,&vbo);
}






Rectangle::~Rectangle(){}


#endif