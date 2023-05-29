#ifndef SHARED_H_
#define SHARED_H_

    #define COLOR_EQUAL(c1,c2) (((c1[0]) == (c2[0])) && ((c1[1]) == (c2[1])) && ((c1[2]) == (c2[2])))
    #define PRINT_OP(op) switch (op) { \
                                case op_R:      printf("R\n"); break;       \
                                case op_R_inv:  printf("R_inv\n"); break;   \
                                case op_L:      printf("L\n"); break;       \
                                case op_L_inv:  printf("L_inv\n"); break;   \
                                case op_U:      printf("U\n"); break;       \
                                case op_U_inv:  printf("U_inv\n"); break;   \
                                case op_D:      printf("D\n"); break;       \
                                case op_D_inv:  printf("D_inv\n"); break;   \
                                case op_B:      printf("B\n"); break;       \
                                case op_B_inv:  printf("B_inv\n"); break;   \
                                case op_F:      printf("F\n"); break;       \
                                case op_F_inv:  printf("F_inv\n"); break;   \
                            }
    #define PRINT_COLORS(c) printf("%f %f %f| %f %f %f| %f %f %f\n",(c)[0][0],(c)[0][1],(c)[0][2],(c)[1][0],(c)[1][1],(c)[1][2],(c)[2][0],(c)[2][1],(c)[2][2])
    #define PRINT_COLOR(c) printf("%f %f %f\n",(c)[0],(c)[1],(c)[2])



    #define RED {1.f,0.f,0.f}
    #define GREEN {0.f,1.f,0.f}
    #define BLUE {0.f,0.f,1.f}
    #define YELLOW {1.f,1.f,0.f}
    #define WHITE {1.f,1.f,1.f}
    #define ORANGE {1.f,0.65f,0.f}
    
    enum Operation {op_R,op_R_inv,op_L,op_L_inv,op_U,op_U_inv,op_D,op_D_inv,op_B,op_B_inv,op_F,op_F_inv};
    std::vector<std::string> opsAsString = {"op_R","op_R_inv","op_L","op_L_inv","op_U","op_U_inv","op_D","op_D_inv","op_B","op_B_inv","op_F","op_F_inv"};
    

    const Operation RUR_U_[] = {op_R,op_U,op_R_inv,op_U_inv}; 
    const Operation L_U_LU[] = {op_L_inv,op_U_inv,op_L,op_U}; 
    const Operation BUB_U_[] = {op_B,op_U,op_B_inv,op_U_inv};
    const Operation B_U_BU[] = {op_B_inv,op_U_inv,op_B,op_U};
    const Operation URU_L_UR_U_L[] = {op_U,op_R,op_U_inv,op_L_inv,op_U,op_R_inv,op_U_inv,op_L};

    const float WIDTH  = 800.f;
    const float HEIGHT = 600.f; 
    const float rotationsX[8] = {0.f,90.f,0.f,90.f,270.f,180.f,270.f,180.f}; 
    const float rotationsY[8] = {90.f,90.f,0.f,0.f,90.f,90.f,0.f,0.f}; 



    float rotateU = 0.f;
    float rotateL = 0.f;
    float rotateR = 0.f;



    float white[3] = WHITE;  
    float yellow[3] = YELLOW;



    float rotSpeed = 2;


#endif
