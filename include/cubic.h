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

enum Operation {
    op_R,
    op_R_inv,
    op_L,
    op_L_inv,
    op_U,
    op_U_inv,
    op_B,
    op_B_inv,
    op_F,
    op_F_inv,
    op_D,
    op_D_inv,    
};


class Cubic
{
private:
    int size;
    std::vector<Cube> cubes;
    

    bool animate = false;
    float rotR = 0; 
    float rotL = 0; 
    float rotU = 0;
    float rotD = 0;
    float rotF = 0;
    float rotB = 0;

    float rotAxis[3] = {0.f,0.f,0.f}; 
    float currRot = 0.f;

    float currRotX = 0;
    float currRotY = 0.f;
    float start , curr;
    float dur = 0.2;
    std::set<int> parts;
    Operation operation;
    float rotEnd = 0.f;
 
    std::vector<std::vector<std::vector<float>>> colors = { //right front top
        {RED,GREEN,YELLOW},  
        {RED,WHITE,GREEN},
        {GREEN,ORANGE,YELLOW},
        {WHITE,ORANGE,GREEN},
        
        {RED,YELLOW,BLUE},
        {RED,BLUE,WHITE},
        {YELLOW,ORANGE,BLUE},
        {BLUE,ORANGE,WHITE},
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


    std::vector<float> rotationsZ = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f}; 
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
                    Cube cube = Cube(colors[counter]);
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

    void after_anim() {
        switch (operation) {
            case op_R:  R(); break;
            case op_R_inv:  R_inv(); break; 
            case op_L:  L(); break;
            case op_L_inv:  L_inv(); break; 
            case op_U:  U(); break;
            case op_U_inv:  U_inv(); break; 
            case op_D:  D(); break;
            case op_D_inv:  D_inv(); break;             
            case op_B:  B(); break;
            case op_B_inv:  B_inv(); break; 
            case op_F:  F(); break;
            case op_F_inv:  F_inv(); break; 
        }
    }
    void init_anim(int p[4],Operation op,int axis,int inv = 1) {
        if(animate) return;
        switch (axis) {
            case 0:  rotAxis[0] = -inv; rotAxis[1] = 0; rotAxis[2] = 0; break;
            case 1:  rotAxis[0] = 0; rotAxis[1] = -inv; rotAxis[2] = 0; break;
            case 2:  rotAxis[0] = 0; rotAxis[1] = 0; rotAxis[2] = -inv; break;
        }

        animate = true;
        start = glfwGetTime();
        curr = 0;

        operation = op;
        
        parts.clear();
        for(int i = 0; i < 4 ; i++)
            parts.insert(p[i]);

    }
    void update_anim() {
        if(! animate) return;
        curr = glfwGetTime() - start;

        currRot = 90.f * curr/dur;
        // switch (operation)
        // {
        //     case op_L_inv: 
        //     case op_R:  currRotX = -90.f * curr/dur;  break;
            
        //     case op_L:  
        //     case op_R_inv:  currRotX =  90.f  * curr/dur;  break;

        //     case op_U:  currRotY =  -90.f  * curr/dur; break;
        //     case op_U_inv:  currRotY = 90.f  * curr/dur; break; 
            
            
        //     case op_B:  B(); break;
        //     case op_B_inv:  B_inv(); break; 
        //     case op_F:  currRotZ =  -90.f  * curr/dur; break;
        //     case op_F_inv:  currRotZ =  -90.f  * curr/dur; break; 
        // }        
        printf("%f %f %f\n",dur,curr,currRotX);
        if(curr >= dur) {
            animate = false;
            currRot = 0;
            parts.clear();
            after_anim();
        }
    }

    void R() {
        printf("R\n");  
        int Rp[] = {0 , 1 ,5 , 4 };
        std::vector<std::vector<float>> tmp = cubes[Rp[0]].colors;
        for(int i = 0; i < 3 ; i++) {
            cubes[Rp[i]].setColor(cubes[Rp[i + 1]].colors);            
        }
        cubes[Rp[3]].setColor(tmp);


    }
    void R_inv() {
        printf("R_inv\n");
        int Rp[] = {0 , 4 , 5 , 1 }; // 0 -> 4 -> 5 -> 1
        std::vector<std::vector<float>> tmp = cubes[Rp[0]].colors;
        for(int i = 0; i < 3 ; i++) {
            cubes[Rp[i]].setColor(cubes[Rp[i + 1]].colors);            
        }
        cubes[Rp[3]].setColor(tmp);
    
    }
    
    void L()     {
        printf("L \n");

        int Rp[] = {2 , 6 ,7 , 3 }; // 2 -> 6 -> 7 -> 2
        std::vector<std::vector<float>> tmp = cubes[Rp[0]].colors;
        for(int i = 0; i < 3 ; i++) {
            cubes[Rp[i]].setColor(cubes[Rp[i + 1]].colors);            
        }
        cubes[Rp[3]].setColor(tmp);
    }
    void L_inv() {
        printf("L_inv\n");
  int Rp[] = {2 , 3 ,7 , 6 }; // 2 -> 3 -> 7 -> 6
        std::vector<std::vector<float>> tmp = cubes[Rp[0]].colors;
        for(int i = 0; i < 3 ; i++) {
            cubes[Rp[i]].setColor(cubes[Rp[i + 1]].colors);            
        }
        cubes[Rp[3]].setColor(tmp);
    } 

    void U() {
        printf("U\n");  
        int order[] = {0 , 4 , 6 ,2}; // 0 -> 4 -> 6 -> 2 -> 0
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[0],cubes[order[0]].colors[1],cubes[order[0]].colors[2]},
            {cubes[order[1]].colors[2],cubes[order[1]].colors[0],cubes[order[1]].colors[1]},
            {cubes[order[2]].colors[2],cubes[order[2]].colors[0],cubes[order[2]].colors[1]},
            {cubes[order[3]].colors[2],cubes[order[3]].colors[0],cubes[order[3]].colors[1]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);
    }     
    void U_inv() {
        printf("U_inv\n");
        int Up[] = {0 , 2 ,6 , 4 };
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[Up[0]].colors[1],cubes[Up[0]].colors[2],cubes[Up[0]].colors[0]},
            {cubes[Up[1]].colors[0],cubes[Up[1]].colors[1],cubes[Up[1]].colors[2]},
            {cubes[Up[2]].colors[1],cubes[Up[2]].colors[2],cubes[Up[2]].colors[0]},
            {cubes[Up[3]].colors[1],cubes[Up[3]].colors[2],cubes[Up[3]].colors[0]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[Up[i]].setColor(colors[i + 1]);            
        }
        cubes[Up[3]].setColor(tmpCol);
    }

    void D() {
        printf("D\n");  
        int order[] = {1 , 5 , 7 ,3}; // 1 -> 5 -> 7 -> 3 -> 1
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[1],cubes[order[0]].colors[2],cubes[order[0]].colors[0]},
            {cubes[order[1]].colors[1],cubes[order[1]].colors[2],cubes[order[1]].colors[0]},
            {cubes[order[2]].colors[0],cubes[order[2]].colors[1],cubes[order[2]].colors[2]},
            {cubes[order[3]].colors[1],cubes[order[3]].colors[2],cubes[order[3]].colors[0]},
        };
        
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);           
     
    }
    void D_inv() {
        printf("D_inv\n");  
        int order[] = {1 , 3 , 7 ,5}; // 1 -> 3 -> 7 -> 5 -> 1
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[2],cubes[order[0]].colors[0],cubes[order[0]].colors[1]},
            {cubes[order[1]].colors[2],cubes[order[1]].colors[0],cubes[order[1]].colors[1]},
            {cubes[order[2]].colors[2],cubes[order[2]].colors[0],cubes[order[2]].colors[1]},
            {cubes[order[3]].colors[0],cubes[order[3]].colors[1],cubes[order[3]].colors[2]},
        };
        
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);           
    }    
    

    void F() {
        printf("F\n");
        int order[] = {0 , 2 , 3 ,1}; 
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[2],cubes[order[0]].colors[0],cubes[order[0]].colors[1]},
            {cubes[order[1]].colors[2],cubes[order[1]].colors[0],cubes[order[1]].colors[1]},
            {cubes[order[2]].colors[2],cubes[order[2]].colors[0],cubes[order[2]].colors[1]},
            {cubes[order[3]].colors[0],cubes[order[3]].colors[1],cubes[order[3]].colors[2]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);          
    }
    void F_inv() {
        printf("F_inv\n");
        int order[] = {0 , 1 , 3 ,2}; 
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[1],cubes[order[0]].colors[2],cubes[order[0]].colors[0]},
            {cubes[order[1]].colors[1],cubes[order[1]].colors[2],cubes[order[1]].colors[0]},
            {cubes[order[2]].colors[0],cubes[order[2]].colors[1],cubes[order[2]].colors[2]},
            {cubes[order[3]].colors[1],cubes[order[3]].colors[2],cubes[order[3]].colors[0]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);          
    }
    
    void B() {
        printf("B\n");
        int order[] = {4 , 5 ,7 ,6}; 
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[0],cubes[order[0]].colors[1],cubes[order[0]].colors[2]},
            {cubes[order[1]].colors[2],cubes[order[1]].colors[0],cubes[order[1]].colors[1]},
            {cubes[order[2]].colors[2],cubes[order[2]].colors[0],cubes[order[2]].colors[1]},
            {cubes[order[3]].colors[2],cubes[order[3]].colors[0],cubes[order[3]].colors[1]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);            
    }
    void B_inv() {
        printf("B_inv\n");
        int order[] = {4 , 6 ,7 ,5}; 
        std::vector<std::vector<std::vector<float>>> colors = {
            {cubes[order[0]].colors[1],cubes[order[0]].colors[2],cubes[order[0]].colors[0]},
            {cubes[order[1]].colors[0],cubes[order[1]].colors[1],cubes[order[1]].colors[2]},
            {cubes[order[2]].colors[1],cubes[order[2]].colors[2],cubes[order[2]].colors[0]},
            {cubes[order[3]].colors[1],cubes[order[3]].colors[2],cubes[order[3]].colors[0]},
        };
        std::vector<std::vector<float>> tmpCol = colors[0];
        for(int i = 0; i < 3 ; i++) {
            cubes[order[i]].setColor(colors[i + 1]);            
        }
        cubes[order[3]].setColor(tmpCol);          
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
            int Rp[] = {0 , 1 ,5 , 4};
            
            init_anim(Rp,op_R,0);            
        }
        else if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS && !once) {
            once = true;
            int Rp[] = {0 , 4 , 5 , 1 }; // 0 -> 4 -> 5 -> 1
            init_anim(Rp,op_R_inv,0,-1);            
        }
        else if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS && !once) {
            once = true;
            int Rp[] = {2 , 3 ,7 , 6 }; // 2 -> 3 -> 7 -> 6
            init_anim(Rp,op_L,0,-1);            
        }
        else if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS && !once) {
            once = true;
            int Rp[] = {2 , 3 ,7 , 6 }; // 2 -> 3 -> 7 -> 6

            init_anim(Rp,op_L_inv,0);            
        }
        else if(glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS && !once) {
            once = true;
            int order[] = {0 , 4 , 6 ,2}; // 0 -> 4 -> 6 -> 2 -> 0
            init_anim(order,op_U,1);            
        }   
        else if(glfwGetKey(window,GLFW_KEY_Y) == GLFW_PRESS && !once) {
            once = true;
            int order[] = {0 , 4 , 6 ,2}; // 0 -> 4 -> 6 -> 2 -> 0
            init_anim(order,op_U_inv,1,-1);            
        }   
        else if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS && !once) {
            once = true;
            int Rp[] = {1 , 3 ,5 , 7 }; // 2 -> 3 -> 7 -> 6
            init_anim(Rp,op_D,1);            
        }    
        else if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS && !once) {
            once = true;
            int Rp[] = {1 , 3 ,5 , 7}; // 2 -> 3 -> 7 -> 6
            init_anim(Rp,op_D_inv,1,-1);            
        }        
        else if(glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS && !once) {
            int order[] = {0 , 1 , 2 ,3};
            init_anim(order,op_F,2);            

            once = true;
        }        
        else if(glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS && !once) {
            int order[] = {0 , 1 , 2 ,3};
            init_anim(order,op_F_inv,2,-1);            
            once = true;
        }            
        else if(glfwGetKey(window,GLFW_KEY_B) == GLFW_PRESS && !once) {
            once = true;
            int order[] = {4 , 5 , 6 ,7};
            init_anim(order,op_B,2,-1); 
        }    
        else if(glfwGetKey(window,GLFW_KEY_V) == GLFW_PRESS && !once) {
            once = true;
            int order[] = {4 , 5 , 6 ,7};
            init_anim(order,op_B_inv,2); 
        }                    
        else if(   glfwGetKey(window,GLFW_KEY_R) == GLFW_RELEASE 
                && glfwGetKey(window,GLFW_KEY_E) == GLFW_RELEASE 
                && glfwGetKey(window,GLFW_KEY_L) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_K) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_U) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_Y) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_D) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_S) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_F) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_G) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_B) == GLFW_RELEASE
                && glfwGetKey(window,GLFW_KEY_V) == GLFW_RELEASE
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

        update_anim(); 

        for (int i = 0; i < 8; i++) {

            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model,glm::vec3(center)); 
                    model = glm::rotate(model,glm::radians(rotateX),glm::vec3(1.f,0.f,0.f));
                    model = glm::rotate(model,glm::radians(rotateY),glm::vec3(0.f,1.f,0.f));

                if(animate) {
                    if(parts.count(i)) {
                        model = glm::rotate(model,glm::radians(currRot),glm::vec3(rotAxis[0],rotAxis[1],rotAxis[2]));
                        // model = glm::rotate(model,glm::radians(currRotX),glm::vec3(1.f,0.f,0.f));
                        // model = glm::rotate(model,glm::radians(currRotY),glm::vec3(0.f,1.f,0.f));
                        // model = glm::rotate(model,glm::radians(currRotZ),glm::vec3(0.f,0.f,1.f));
                    }
                }

                std::set<int> order = {0 , 1 , 2 ,3};
                if(order.count(i)) {
                    model = glm::rotate(model,glm::radians(rotate_angleX),glm::vec3(0.f,0.f,1.f));
                }
            model = glm::translate(model,glm::vec3(-center)); 



            model = glm::translate(model,glm::vec3(poses[i][0],poses[i][1],poses[i][2]) + glm::vec3(cube_x,cube_y,cube_z)); 
            model = glm::rotate(model,glm::radians(rotationsX[i]),glm::vec3(1.f,0.f,0.f));
            model = glm::rotate(model,glm::radians(rotationsZ[i]),glm::vec3(0.f,0.f,1.f));
            model = glm::rotate(model,glm::radians(rotationsY[i]),glm::vec3(0.f,1.f,0.f));
            

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
