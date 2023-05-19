#ifndef CUBIC_H
#define CUBIC_H

#include <vector>

#include "cube.h"
#include "shader.h"
#include "shared.h"

#define RED {1.f,0.f,0.f}
#define GREEN {0.f,1.f,0.f}
#define BLUE {0.f,0.f,1.f}
#define YELLOW {1.f,1.f,0.f}
#define WHITE {1.f,1.f,1.f}
#define ORANGE {1.f,0.65f,0.f}
#define HIDDEN_COLOR {0.f,1.f,1.f}
#define COLOR_SET {BLUE,GREEN,RED,ORANGE,WHITE,YELLOW}
#define CUBE_DATA_INIT(index){COLOR_SET,index,0.f,0.f}

struct CubeData {
    float color[6][3];
    int id;
    float rotationX;
    float rotationY;

};

class Cubic
{
private:
    int size;
    std::vector<Cube> cubes;
    std::vector<CubeData> cubeID = {
        CUBE_DATA_INIT(0), // back front left right down up  
        CUBE_DATA_INIT(1),  
        CUBE_DATA_INIT(2),  
        CUBE_DATA_INIT(3),

        CUBE_DATA_INIT(4), // back front left right down up  
        CUBE_DATA_INIT(5),  
        CUBE_DATA_INIT(6),  
        CUBE_DATA_INIT(7), 
    }; 

    // green blue yellow white red orange

    float cubeZoff = 6;

    std::vector<std::vector<float>> poses;
    float rotateX = 0;
    float rotateY = 0;
    float rotateZ = 0;

    bool once = false;
    float delayMax = 1.f;
    float delayCounter = 0.f;
    float delayOffset = 0.f;

public:
    Cubic(int _size) {
        size = _size;
        float colors[6][3] = {
            {1.f,0.f,0.f},
            {0.f,1.f,0.f},
            {0.f,0.f,1.f},
            {1.f,1.f,0.f},
            {0.f,1.f,1.f},
            {1.f,1.f,1.f},
        };

        int counter = 0;
        for(int z = 0; z < size; z++) {
            for(int x = 0; x < size; x++) {
                for(int y = 0; y < size; y++) {
                    Cube cube = Cube(cubeID[counter].color);
                    std::vector<float> pos;
                    pos.push_back(0.5 - x);
                    pos.push_back(0.5 - y);
                    pos.push_back(-(z + cubeZoff));

                    poses.push_back(pos);
                    cubes.push_back(cube);
                    counter++;
                }
            }
        }

    }

    void R() {
        printf("R\n");  
                        
    }
    void R_inv() {
        printf("R_inv\n");
    }
    void L() {
        printf("L\n");
    }
    void L_inv() {
        printf("L_inv\n");
    } 
    void U() {
        printf("U\n");
    }     
    void U_inv() {
        printf("U_inv\n");
    }



    void input(GLFWwindow* window) {
		if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
            rotateX += 1;
        } else if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
            rotateX -= 1;
        } 
		if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
            rotateY  += 1;
        } else if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
            rotateY  -= 1;
        }         

		if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS && !once) {
            once = true;
            R();
        }
        else if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS && !once) {
            once = true;
            R_inv();
        }
        else if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS && !once) {
            once = true;
            L();
        }
        else if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS && !once) {
            once = true;
            L_inv();
        }
        else if(glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS && !once) {
            once = true;
            U();
        }   
        else if(glfwGetKey(window,GLFW_KEY_Y) == GLFW_PRESS && !once) {
            once = true;
            U_inv();
        }        
        else if(   glfwGetKey(window,GLFW_KEY_R) == GLFW_RELEASE 
                && glfwGetKey(window,GLFW_KEY_E) == GLFW_RELEASE 
                && glfwGetKey(window,GLFW_KEY_L) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_K) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_U) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_Y) == GLFW_RELEASE
                ) {
            if(once && delayCounter < delayMax) {
                delayCounter += glfwGetTime() - delayOffset;
            } else if(delayCounter >= delayMax) {
                delayCounter = 0.f;
                once = false;
            }
        }


    }
    void render(Shader shader){
        glm::mat4 parentModel = glm::mat4(1.0f);

        glm::vec3 center = glm::vec3(0);
        for (int i = 0; i < poses.size(); i++) {
            center += glm::vec3(poses[i][0],poses[i][1],poses[i][2]); 
        }
        center /= poses.size();

        for (int i = 0; i < 8; i++) {
            glm::mat4 model = glm::mat4(1.f);



            model = glm::translate(model,glm::vec3(center)); 
            model = glm::rotate(model,glm::radians(rotateX),glm::vec3(1.f,0.f,0.f));
            model = glm::rotate(model,glm::radians(rotateY),glm::vec3(0.f,1.f,0.f));
            model = glm::translate(model,glm::vec3(-center)); 


            model = glm::translate(model,glm::vec3(poses[i][0],poses[i][1],poses[i][2]) + glm::vec3(cube_x,cube_y,cube_z)); 
            model = glm::rotate(model,glm::radians(cubeID[i].rotationX),glm::vec3(1.f,0.f,0.f));
            model = glm::rotate(model,glm::radians( cubeID[i].rotationY),glm::vec3(0.f,1.f,0.f));

            glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, &model[0][0]);
            cubes[i].render();
        }
    }
    void clean() {
        for(Cube cube : cubes ) {
            cube.clean();
        } 
    }
    ~Cubic() {

    }
};





#endif // CUBIC_H
