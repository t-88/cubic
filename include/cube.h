#ifndef CUBE_H
#define CUBE_H

#include <vector>

// cube -> traingle -> vbo , veb , vax

class Cube
{
private:
   std::vector<float> vertices;
   std::vector<uint32_t> indices;
   float pos[3];


    uint32_t vaoID;
    uint32_t vboID;
    uint32_t eboID;
    
public:
    Cube();
    ~Cube();
    void render();
    void clean();
};

Cube::Cube() {
    vertices = {
                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f, 
                0.5f,  0.5f, -0.5f, 
                0.5f,  0.5f, -0.5f, 
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f, -0.5f,  0.5f,
                0.5f, -0.5f,  0.5f, 
                0.5f,  0.5f,  0.5f, 
                0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f,  0.5f,
                -0.5f, -0.5f,  0.5f,

                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,

                0.5f,  0.5f,  0.5f, 
                0.5f,  0.5f, -0.5f, 
                0.5f, -0.5f, -0.5f, 
                0.5f, -0.5f, -0.5f, 
                0.5f, -0.5f,  0.5f, 
                0.5f,  0.5f,  0.5f, 

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f, 
                0.5f, -0.5f,  0.5f, 
                0.5f, -0.5f,  0.5f, 
                -0.5f, -0.5f,  0.5f,
                -0.5f, -0.5f, -0.5f,

                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f, -0.5f, 
                0.5f,  0.5f,  0.5f, 
                0.5f,  0.5f,  0.5f, 
                -0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f
            };
    indices = {
        0 , 1 , 2 ,
        0 , 2, 3,
    };


    glGenVertexArrays(1,&vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1,&vboID);
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),vertices.data(),GL_STATIC_DRAW);

    glGenBuffers(1,&eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() *  sizeof(uint32_t),indices.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


void Cube::render() {
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES,0,vertices.size());
}

void Cube::clean() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vaoID);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDeleteBuffers(1,&vboID);
}
Cube::~Cube() {
}


#endif 