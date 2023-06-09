#ifndef CUBIC_H_
#define CUBIC_H_

#include <vector>
#include <set>
#include <string>
#include <array>
#include "cube.h"
#include "shader.h"
#include "rectangle.h"


#include "shared.h"
#include "cubic_utils.h"





class Cubic
{
public:
    std::vector<Cube> cubes;
    int shuffelCounter = 20;
    bool randomShuffelMode = false;
    
    bool animate = false;
    float rotAxis[3] = {0.f,0.f,0.f}; 
    float currRot = 0.f;

    float start , curr;
    float dur = 0.05f;

    std::set<int> parts;
    Operation operation;
    float rotEnd = 0.f;


    std::vector<std::vector<std::vector<float>>> colors = { 
        {ORANGE,GREEN,YELLOW},  
        
        {ORANGE,WHITE,GREEN},

        {GREEN,RED,YELLOW},

        {WHITE,RED,GREEN},
        
        {ORANGE,YELLOW,BLUE},

        {ORANGE,BLUE,WHITE},
        
        {YELLOW,RED,BLUE},
        
        {BLUE,RED,WHITE},
    };
    float cubeZoff = 8;

    std::vector<std::vector<float>> poses;
    float rotateX = 0;
    float rotateY = 0;
    float rotateZ = 0;

    bool updateRender2d = true;

    std::vector<std::array<int,4>> orientation = {
        {0,1,4,5},
        {2,3,6,7},
        {0,2,4,6},
        {1,3,5,7},
        {4,5,6,7},
        {0,1,2,3},
    };
        
    glm::vec3 center = glm::vec3(0);
    std::vector<Rectangle> rects;

public:
    std::vector<int> order = {0,1,2,3,4,5,6,7};
    bool doingOps = false;
    std::vector<Operation> opsInProgress;


    Cubic(int _size);
    Cubic();
    void init();

    void after_anim();
    void init_anim(std::array<int,4> p,Operation op,int axis,int inv);
    void update_anim();

    void R();
    void R_inv();
    void L();
    void L_inv();
    void U();    
    void U_inv();
    void D();
    void D_inv();   
    void F();
    void F_inv();
    void B();
    void B_inv();



    std::pair<std::vector<int>,std::vector<Cube>> do_op(Operation op,std::pair<std::vector<int>,std::vector<Cube>> output);
    void do_ops();
    void activate_doing_ops(std::vector<Operation> ops);
    void activate_random_shuffel_mode();
    void apply_order(std::pair<std::vector<int>,std::vector<Cube>>);
   

    void input(GLFWwindow* window);
    void render(Shader shader,GLFWwindow* window);
    void render2D(Shader shader,GLFWwindow* window);
    void clean();
};

Cubic::Cubic() {
    
}



void Cubic::apply_order(std::pair<std::vector<int>,std::vector<Cube>> output) {
    for(int i = 0; i < output.second.size(); i++)  cubes[i].setColor(output.second[i].colors);
}

// animation rotations  
void Cubic::after_anim() {
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
    
    
    updateRender2d = true;
    
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(same_colors(colors[i],cubes[j].colors)) {
                order[i] = j;
                break;
            }
        }
    }



}
void Cubic::init() {
    int counter = 0;

    for(int z = 0; z < 2; z++) {

        for(int x = 0; x < 2; x++) {
            for(int y = 0; y < 2; y++) {
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


    for (int i = 0; i < poses.size(); i++)
        center += glm::vec3(poses[i][0],poses[i][1],poses[i][2]); 
    center /= poses.size();


    int w = 20;  
    int h = 20; 
    int off = 5;

    int xOff = 2 * w + off;  
    int yOff = 0; 

    for(int i = 0; i < 4; i++) {
        for(int x = 1; x >= 0; x--) 
            for(int y = 0; y < 2; y++) 
                rects.push_back(Rectangle(w * x + xOff,h * y + yOff,w,h));
        yOff += 2 * h + off;
    }

    xOff += 2 * w + off;
    yOff = 2 * h + off;
    for(int x = 1; x >= 0;  x--) 
        for(int y = 0; y < 2; y++) 
            rects.push_back(Rectangle(w * x + xOff,h * y + yOff,w,h));

    xOff = 0;
    for(int x = 1; x >= 0; x--) 
        for(int y = 0; y < 2; y++) 
            rects.push_back(Rectangle(w * x + xOff,h * y + yOff,w,h));
}
void Cubic::init_anim(std::array<int,4> p,Operation op,int axis,int inv) {
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
void Cubic::update_anim() {
    if(! animate) return;
    curr = glfwGetTime() - start;
    currRot = 90.f * curr/dur;
    if(curr >= dur) {
        animate = false;
        currRot = 0;
        parts.clear();
        after_anim();
    }
}

// input
void Cubic::input(GLFWwindow* window) {
    // camera like system (rotating all the cube)
	if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)  rotateX += 1;
    else if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS)  rotateX -= 1;
	if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)  rotateY  += 1;
    else if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)  rotateY  -= 1;
             
    if(animate) return; // delay on input
    // rotation input

    
	if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS) 
        init_anim(orientation[(int)op_R/2],op_R,0,1);            
    else if(glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS)
        init_anim(orientation[(int)op_R_inv/2],op_R_inv,0,-1);            
    else if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS)
        init_anim(orientation[(int)op_L/2],op_L,0,-1);            
    else if(glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS)
        init_anim(orientation[(int)op_L_inv/2],op_L_inv,0,1);            
    else if(glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS)
        init_anim(orientation[(int)op_U/2],op_U,1,1);            
    else if(glfwGetKey(window,GLFW_KEY_Y) == GLFW_PRESS)
        init_anim(orientation[(int)op_U_inv/2],op_U_inv,1,-1);            
    else if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        init_anim(orientation[(int)op_D/2],op_D,1,1);            
    else if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        init_anim(orientation[(int)op_D_inv/2],op_D_inv,1,-1);            
    else if(glfwGetKey(window,GLFW_KEY_F) == GLFW_PRESS)
        init_anim(orientation[(int)op_F/2],op_F,2,1);            
    else if(glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS)
        init_anim(orientation[(int)op_F_inv/2],op_F_inv,2,-1);            
    else if(glfwGetKey(window,GLFW_KEY_B) == GLFW_PRESS)
        init_anim(orientation[(int)op_B/2],op_B,2,-1); 
    else if(glfwGetKey(window,GLFW_KEY_V) == GLFW_PRESS)
        init_anim(orientation[(int)op_B_inv/2],op_B_inv,2,1); 
                        
}


void Cubic::activate_random_shuffel_mode() {
    if(randomShuffelMode) return;
    shuffelCounter = 20;
    std::vector<Operation> randOps;
    for(int i = 0; i < shuffelCounter; i++)  randOps.push_back((Operation) (rand() % 12));
    activate_doing_ops(randOps);
}
void Cubic::activate_doing_ops(std::vector<Operation> ops) {
    doingOps = true;
    opsInProgress =  ops;
}
void Cubic::do_ops() {
    if(!doingOps) return;

    if(!animate) {
        if(opsInProgress.size() == 0) {
            doingOps = false;
            return;
        }
        int dirs[] = {1,-1,-1,1,1,-1,1,-1,-1,1,1,-1};
        init_anim(orientation[(int)opsInProgress[0]/2],opsInProgress[0],(int)opsInProgress[0]/4,dirs[opsInProgress[0]]);
        opsInProgress.erase(opsInProgress.begin());
    }
}

std::pair<std::vector<int>,std::vector<Cube>> Cubic::do_op(Operation op,std::pair<std::vector<int>,std::vector<Cube>> output) {
        std::vector<int> tmpOrder(order);
        std::vector<Cube> tmpCubes(cubes);

        order = output.first;

        for(int i = 0; i < output.second.size(); i++)  cubes[i].setColor(output.second[i].colors);
        

        switch (op) {
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

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(same_colors(colors[i],cubes[j].colors)) {
                order[i] = j;
                break;
            }
        }
    }

    output.first = order;
    output.second = cubes;



    order = tmpOrder;
    cubes = tmpCubes;
    for(int i = 0; i < cubes.size(); i++)  cubes[i].setColor(tmpCubes[i].colors);
    
    return output;
}


// render
void Cubic::render(Shader shader,GLFWwindow* window){
    input(window);
    update_anim(); 
    do_ops();

    dur = rotSpeed / 10;

    for (int i = 0; i < 8; i++) {
        glm::mat4 model = glm::mat4(1.f);
        
        model = glm::translate(model,glm::vec3(center)); 
            model = glm::rotate(model,glm::radians(rotateX),glm::vec3(1.f,0.f,0.f));
            model = glm::rotate(model,glm::radians(rotateY),glm::vec3(0.f,1.f,0.f));
            if(animate && parts.count(i))
                model = glm::rotate(model,glm::radians(currRot),glm::vec3(rotAxis[0],rotAxis[1],rotAxis[2]));
        model = glm::translate(model,glm::vec3(-center)); 
        model = glm::translate(model,glm::vec3(poses[i][0],poses[i][1],poses[i][2])); 
        model = glm::rotate(model,glm::radians(rotationsX[i]),glm::vec3(1.f,0.f,0.f));
        model = glm::rotate(model,glm::radians(rotationsY[i]),glm::vec3(0.f,1.f,0.f));
        glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, &model[0][0]);
        cubes[i].render();
    }
}
void Cubic::render2D(Shader shader,GLFWwindow* window){
    shader.activate();

    if(updateRender2d) {
        updateRender2d = true;

        rects[0 * 4 + 0].setColor(cubes[4].colors[2][0],cubes[4].colors[2][1],cubes[4].colors[2][2]);
        rects[0 * 4 + 1].setColor(cubes[5].colors[1][0],cubes[5].colors[1][1],cubes[5].colors[1][2]);
        rects[0 * 4 + 2].setColor(cubes[6].colors[2][0],cubes[6].colors[2][1],cubes[6].colors[2][2]);
        rects[0 * 4 + 3].setColor(cubes[7].colors[0][0],cubes[7].colors[0][1],cubes[7].colors[0][2]);

        rects[1 * 4 + 0].setColor(cubes[5].colors[2][0],cubes[5].colors[2][1],cubes[5].colors[2][2]);
        rects[1 * 4 + 1].setColor(cubes[1].colors[1][0],cubes[1].colors[1][1],cubes[1].colors[1][2]);
        rects[1 * 4 + 2].setColor(cubes[7].colors[2][0],cubes[7].colors[2][1],cubes[7].colors[2][2]);
        rects[1 * 4 + 3].setColor(cubes[3].colors[0][0],cubes[3].colors[0][1],cubes[3].colors[0][2]);

        rects[2 * 4 + 0].setColor(cubes[0].colors[1][0],cubes[0].colors[1][1],cubes[0].colors[1][2]);
        rects[2 * 4 + 1].setColor(cubes[1].colors[2][0],cubes[1].colors[2][1],cubes[1].colors[2][2]);
        rects[2 * 4 + 2].setColor(cubes[2].colors[0][0],cubes[2].colors[0][1],cubes[2].colors[0][2]);
        rects[2 * 4 + 3].setColor(cubes[3].colors[2][0],cubes[3].colors[2][1],cubes[3].colors[2][2]);

        rects[3 * 4 + 0].setColor(cubes[4].colors[1][0],cubes[4].colors[1][1],cubes[4].colors[1][2]);
        rects[3 * 4 + 1].setColor(cubes[0].colors[2][0],cubes[0].colors[2][1],cubes[0].colors[2][2]);
        rects[3 * 4 + 2].setColor(cubes[6].colors[0][0],cubes[6].colors[0][1],cubes[6].colors[0][2]);
        rects[3 * 4 + 3].setColor(cubes[2].colors[2][0],cubes[2].colors[2][1],cubes[2].colors[2][2]);



        rects[4 * 4 + 0].setColor(cubes[4].colors[0][0],cubes[4].colors[0][1],cubes[4].colors[0][2]);
        rects[4 * 4 + 1].setColor(cubes[5].colors[0][0],cubes[5].colors[0][1],cubes[5].colors[0][2]);
        rects[4 * 4 + 2].setColor(cubes[0].colors[0][0],cubes[0].colors[0][1],cubes[0].colors[0][2]);
        rects[4 * 4 + 3].setColor(cubes[1].colors[0][0],cubes[1].colors[0][1],cubes[1].colors[0][2]);


        rects[5 * 4 + 0].setColor(cubes[2].colors[1][0],cubes[2].colors[1][1],cubes[2].colors[1][2]);
        rects[5 * 4 + 1].setColor(cubes[3].colors[1][0],cubes[3].colors[1][1],cubes[3].colors[1][2]);
        rects[5 * 4 + 2].setColor(cubes[6].colors[1][0],cubes[6].colors[1][1],cubes[6].colors[1][2]);
        rects[5 * 4 + 3].setColor(cubes[7].colors[1][0],cubes[7].colors[1][1],cubes[7].colors[1][2]);
    }

    
    
    for(Rectangle rect: rects) {
        rect.render(shader);
    }
}



// applying rotations
void Cubic::R() {
    int order[] = {0 , 1 ,5 , 4 };
    std::vector<std::vector<float>> tmp = cubes[order[0]].colors;
    for(int i = 0; i < 3 ; i++) {
        cubes[order[i]].setColor(cubes[order[i + 1]].colors);            
    }
    cubes[order[3]].setColor(tmp);
}
void Cubic::R_inv() {
    int order[] = {0 , 4 , 5 , 1 }; // 0 -> 4 -> 5 -> 1
    std::vector<std::vector<float>> tmp = cubes[order[0]].colors;
    for(int i = 0; i < 3 ; i++) {
        cubes[order[i]].setColor(cubes[order[i + 1]].colors);            
    }
    cubes[order[3]].setColor(tmp);
}

void Cubic::L()     {
    int order[] = {2 , 6 ,7 , 3 }; 
    std::vector<std::vector<float>> tmp = cubes[order[0]].colors;
    for(int i = 0; i < 3 ; i++) {
        cubes[order[i]].setColor(cubes[order[i + 1]].colors);            
    }
    cubes[order[3]].setColor(tmp);
}
void Cubic::L_inv() {
    int order[] = {2 , 3 ,7 , 6 }; 
    std::vector<std::vector<float>> tmp = cubes[order[0]].colors;
    for(int i = 0; i < 3 ; i++) {
        cubes[order[i]].setColor(cubes[order[i + 1]].colors);            
    }
    cubes[order[3]].setColor(tmp);
} 
    
void Cubic::U() {
    int order[] = {0 , 4 , 6 ,2}; 
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
void Cubic::U_inv() {
    int order[] = {0 , 2 ,6 , 4 };
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

void Cubic::D() {
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
void Cubic::D_inv() {
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
    
void Cubic::F() {
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
void Cubic::F_inv() {
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
    
void Cubic::B() {
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
void Cubic::B_inv() {
    int order[] = {4 , 6 ,7 ,5}; 
    std::vector<std::vector<std::vector<float>>> colors = {
        {cubes[order[0]].colors[1],cubes[order[0]].colors[2],cubes[order[0]].colors[0]},
        {cubes[order[1]].colors[0],cubes[order[1]].colors[1],cubes[order[1]].colors[2]},
        {cubes[order[2]].colors[1],cubes[order[2]].colors[2],cubes[order[2]].colors[0]},
        {cubes[order[3]].colors[1],cubes[order[3]].colors[2],cubes[order[3]].colors[0]},
    };
    std::vector<std::vector<float>> tmp = colors[0];
    for(int i = 0; i < 3 ; i++) {
        cubes[order[i]].setColor(colors[i + 1]);            
    }
    cubes[order[3]].setColor(tmp);          
}

// clean
void Cubic::clean() {
    for(Cube cube : cubes ) cube.clean();
}
#endif // CUBIC_H_
