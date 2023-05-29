#ifndef SHARED_H
#define SHARED_H

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

    #define MAX_SOLVE_STEPS 10
    #define RED {1.f,0.f,0.f}
    #define GREEN {0.f,1.f,0.f}
    #define BLUE {0.f,0.f,1.f}
    #define YELLOW {1.f,1.f,0.f}
    #define WHITE {1.f,1.f,1.f}
    #define ORANGE {1.f,0.65f,0.f}

    


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

    Operation allOps[] = {
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


    float white[3] = WHITE;  
    float yellow[3] = YELLOW;



bool arr_equal(std::vector<std::vector<float>> arr1,std::vector<std::vector<float>> arr2) {
    // takes colors and checks if they are the same
    for(int i = 0; i < arr1.size(); i++) {
        bool found = true;

        for(int j = 0; j < arr2.size(); j++) {
            bool checked = true;
            found = false;
            for(int x = 0; x < arr2[j].size(); x++) {
                if(arr1[i][x] != arr2[j][x]) {
                    checked = false;
                    break;
                } 
            }
            if(checked) {
                found = true;
                break;
            }
    }
        if(!found) return false;
    }
    return true;



}

int index_of(std::vector<std::vector<float>> colors, float* color) {
    for(int i = 0; i < 3; i++) {
        if(COLOR_EQUAL(colors[i],color)) {
            return i;
        }
    }
    return -1;
}
    
#endif
