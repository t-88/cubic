
#ifndef SHARED_H
#define SHARED_H

    #define MAX_SOLVE_STEPS 10


    const float WIDTH  = 800.f;
    const float HEIGHT = 600.f;  

    float cube_x = 0;
    float cube_y = 0;
    float cube_z = 0;

    float rotateU = 0.f;
    float rotateL = 0.f;
    float rotateR = 0.f;

    float rotate_angleX = 0;
    float rotate_angleY = 0;

    enum Operation {
        op_R,
        op_R_inv,
        op_L,
        op_L_inv,
        op_U,
        op_U_inv,
        op_D,
        op_D_inv,      
        op_B,
        op_B_inv,
        op_F,
        op_F_inv,
        Noth,
    };

    Operation ops[] = {
            op_R,
            op_R_inv,
            op_L,
             op_L_inv,
            op_U,
            op_U_inv,
            op_D,
            op_D_inv,      
            op_B,
            op_B_inv,
            op_F,
            op_F_inv,
        };
    float rotationsX[8] = {0.f,90.f,0.f,90.f,270.f,180.f,270.f,180.f}; 
    float rotationsY[8] = {90.f,90.f,0.f,0.f,90.f,90.f,0.f,0.f}; 



    
#endif
