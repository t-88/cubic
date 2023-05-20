#ifndef CUBIC_H
#define CUBIC_H

#include <vector>
#include <set>
#include <string>
#include "cube.h"
#include "shader.h"
#include "shared.h"


#define RED {1.f,0.f,0.f}
#define GREEN {0.f,1.f,0.f}
#define BLUE {0.f,0.f,1.f}
#define YELLOW {1.f,1.f,0.f}
#define WHITE {1.f,1.f,1.f}
#define ORANGE {1.f,0.65f,0.f}
#define PURPLE {62.7f/255,32.f/255,240.f/255}
#define PINK {1.f,0.75f,0.79f}


#define COLOR_SET {BLUE,GREEN,RED,ORANGE,WHITE,YELLOW}
#define CUBE_DATA_INIT(index){COLOR_SET,index,0.f,0.f,{0.f,1.f,0.f}}
// #define PRINT_CUBE printf("%s %s \n%s %s \n -- \n%s %s \n%s %s\n",ids[order[2]],ids[order[0]],ids[order[3]],ids[order[1]],ids[order[6]],ids[order[4]],ids[order[7]],ids[order[5]]);


struct CubeData {
    float color[6][3];
    int id;
    float rotationX;
    float rotationY;
    float rotation[3];

};
struct Face {
    float color[3];
};


class Cubic
{
private:
    int size;
    std::vector<Cube> cubes;
    // std::vector<CubeData> cubeID = {
    //     // {{BLUE,BLUE,BLUE,BLUE,BLUE,BLUE},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{RED,RED,RED,RED,RED,RED},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{GREEN,GREEN,GREEN,GREEN,GREEN,GREEN},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // 
    //     // {{ORANGE,ORANGE,ORANGE,ORANGE,ORANGE,ORANGE},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{PURPLE,PURPLE,PURPLE,PURPLE,PURPLE,PURPLE},0,0.f,0.f,{0.f,1.f,0.f}},
    //     // {{PINK,PINK,PINK,PINK,PINK,PINK},0,0.f,0.f,{0.f,1.f,0.f}},

    //     CUBE_DATA_INIT(0),  
    //     CUBE_DATA_INIT(1),  
    //     CUBE_DATA_INIT(2),  
    //     CUBE_DATA_INIT(3),

    //     CUBE_DATA_INIT(4), 
    //     CUBE_DATA_INIT(5),  
    //     CUBE_DATA_INIT(6),  
    //     CUBE_DATA_INIT(7), 
    // }; 
    std::vector<std::vector<float>> colors = {
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
        {RED,GREEN,BLUE},
    };
    std::string ids[8] = {
        "BLUE",
        "RED",
        "GREEN",
        "YELLOW",
        "ORANGE",
        "WHITE",
        "PURPLE",
        "PINK"
    };


    float cubeZoff = 6;

    int order[8] = {0,1,2,3,4,5,6,7};

    std::vector<float> rotationsX = {0.f,90.f,0.f,90.f,270.f,180.f,270.f,180.f}; 
    std::vector<float> rotationsY = {90.f,90.f,0.f,0.f,90.f,90.f,0.f,0.f}; 



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

        int counter = 0;
        for(int z = 0; z < size; z++) {
            for(int x = 0; x < size; x++) {
                for(int y = 0; y < size; y++) {
                    Cube cube = Cube(colors[counter].data);
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

        printf("%d %d \n%d %d \n -- \n%d %d \n%d %d\n",order[2],order[0],order[3],order[1],order[6],order[4],order[7],order[5]);
        printf("%s %s \n%s %s \n -- \n%s %s \n%s %s\n",ids[order[2]].c_str(),ids[order[0]].c_str(),ids[order[3]].c_str(),ids[order[1]].c_str(),ids[order[6]].c_str(),ids[order[4]].c_str(),ids[order[7]].c_str(),ids[order[5]].c_str());
    }

    void R() {
        printf("R\n");  

        int tmp = order[0];
        order[0] = order[1];
        order[1] = order[5];
        order[5] = order[4];
        order[4] = tmp;
        printf("%d %d \n%d %d \n -- \n%d %d \n%d %d\n",order[2],order[0],order[3],order[1],order[6],order[4],order[7],order[5]);
        printf("%s %s \n%s %s \n -- \n%s %s \n%s %s\n",ids[order[2]].c_str(),ids[order[0]].c_str(),ids[order[3]].c_str(),ids[order[1]].c_str(),ids[order[6]].c_str(),ids[order[4]].c_str(),ids[order[7]].c_str(),ids[order[5]].c_str());

    }
    void R_inv() {printf("R_inv\n");}
    void L()     {printf("L \n");}
    void L_inv() {printf("L_inv\n");} 


    void U() {
        printf("U\n");  

        int tmp = order[0];order[0] = order[4]; order[4] = order[6]; order[6] = order[2]; order[2] = tmp;


        printf("%d %d \n%d %d \n -- \n%d %d \n%d %d\n",order[2],order[0],order[3],order[1],order[6],order[4],order[7],order[5]);
        printf("%s %s \n%s %s \n -- \n%s %s \n%s %s\n",ids[order[2]].c_str(),ids[order[0]].c_str(),ids[order[3]].c_str(),ids[order[1]].c_str(),ids[order[6]].c_str(),ids[order[4]].c_str(),ids[order[7]].c_str(),ids[order[5]].c_str());

    }     
    void U_inv() {printf("U_inv\n");}



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
            // R_inv();
            printf("%s %s \n%s %s \n -- \n%s %s \n%s %s\n",ids[order[2]].c_str(),ids[order[0]].c_str(),ids[order[3]].c_str(),ids[order[1]].c_str(),ids[order[6]].c_str(),ids[order[4]].c_str(),ids[order[7]].c_str(),ids[order[5]].c_str());
        
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
        glm::vec3 center = glm::vec3(0);
        for (int i = 0; i < poses.size(); i++) {
            center += glm::vec3(poses[i][0],poses[i][1],poses[i][2]); 
        }
        center /= poses.size();

        for (int i = 0; i < 1; i++) {

            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model,glm::vec3(center)); 
                model = glm::rotate(model,glm::radians(rotateX),glm::vec3(1.f,0.f,0.f));
                model = glm::rotate(model,glm::radians(rotateY),glm::vec3(0.f,1.f,0.f));
            model = glm::translate(model,glm::vec3(-center)); 


            model = glm::translate(model,glm::vec3(center)); 
                std::set<int> a = {0,1,4,5};
            model = glm::translate(model,glm::vec3(-center)); 


            model = glm::translate(model,glm::vec3(poses[i][0],poses[i][1],poses[i][2]) + glm::vec3(cube_x,cube_y,cube_z)); 
            model = glm::rotate(model,glm::radians(rotationsX[i]),glm::vec3(1.f,0.f,0.f));
            model = glm::rotate(model,glm::radians(rotationsY[i]),glm::vec3(0.f,1.f,0.f));
            

            glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, &model[0][0]);
            cubes[order[i]].render();
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
