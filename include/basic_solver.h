#ifndef BASIC_SOLVER
#define BASIC_SOLVER

#include "cubic.h"
#include "solver.h"
#include <algorithm>

#define DEBUG_SOLVE_STEP true
#define PRINT_SOLVE_STEP_ARGS(arg,...) if (DEBUG_SOLVE_STEP) printf((arg),__VA_ARGS__)
#define PRINT_SOLVE_STEP(arg) if (DEBUG_SOLVE_STEP) printf((arg))
#define PRINT_COLORS(c) printf("%f %f %f| %f %f %f| %f %f %f\n",(c)[0][0],(c)[0][1],(c)[0][2],(c)[1][0],(c)[1][1],(c)[1][2],(c)[2][0],(c)[2][1],(c)[2][2])
#define PRINT_COLOR(c) printf("%f %f %f\n",(c)[0],(c)[1],(c)[2])


// warning dont use those macros they need ops                
#define DO_OP(op) output = cube.do_op(op,output); ops.push_back(op); 
#define REPEAT_OP(op,times) for(int j__ = 0; j__ < times; j__++)  { DO_OP(op);}
#define DO_OPS(operations) for(auto op: (operations)) { DO_OP(op);}



class BasicSolver : Solver
{
private:
public:
    std::pair<std::vector<int>,std::vector<Cube>> output;

    BasicSolver();
    
std::vector<Operation> solve(Cubic cube);
    bool is_combatable(std::vector<Cube>, int , int,int*);
    int color_exist(std::vector<std::vector<float>>, float color[]);
    bool correctTop(std::vector<Cube> cubes);
    
    bool is_solved(std::vector<int>);
    ~BasicSolver();
};

BasicSolver::BasicSolver(){}
int BasicSolver::color_exist(std::vector<std::vector<float>> colors, float color[]){
    for (size_t i = 0; i < 3; i++)
        if(COLOR_EQUAL(colors[i],color)) return i;
    return -1;
}
bool BasicSolver::is_combatable(std::vector<Cube> cubes, int i1, int i2,int* compPos) {
    for(int i = 0; i < 3 ; i++){
        int face = color_exist(cubes[i1].colors,cubes[i2].colors[i].data());
        if(!COLOR_EQUAL(cubes[i2].colors[i],white) &&  face !=  -1) {
            *compPos = face;
            return true; 
        }
    }

    return false;
}

bool BasicSolver::correctTop(std::vector<Cube> cubes) {
    for(int i = 0 ; i < 4 ; i++) {
        for(auto color : cubes[2 * i].colors) {
            if(!COLOR_EQUAL(color,yellow)) {
                if(color_exist(cubes[2*i+1].colors,color.data()) == -1) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<Operation> BasicSolver::solve(Cubic cube) {
    std::vector<Operation> ops;
    output.first =  cube.order;
    output.second =  cube.cubes;

    int topOrder   []= {0,2,6,4};
    int bottomOrder[] = {1,3,7,5};

    Operation RUR_U_[] = {op_R,op_U,op_R_inv,op_U_inv}; 
    Operation L_U_LU[] = {op_L_inv,op_U_inv,op_L,op_U}; 
    Operation BUB_U_[] = {op_B,op_U,op_B_inv,op_U_inv};
    Operation B_U_BU[] = {op_B_inv,op_U_inv,op_B,op_U};
    Operation URU_L_UR_U_L[] = {op_U,op_R,op_U_inv,op_L_inv,op_U,op_R_inv,op_U_inv,op_L};




    // we put a white block at index 1
    {
        int findWhite = -1;
        do {
            for(int i = 0; i < 4; i++) {
                if(color_exist(output.second[2*i+1].colors,white) != -1) {
                    findWhite = i;
                    break;
                }
            }
            if(findWhite == -1) {
                printf("%d \n",findWhite);
                DO_OP(op_F);
                DO_OP(op_F);
                DO_OP(op_B);
                DO_OP(op_B);
            }  
        } while(findWhite == -1);
        int rotateOrder[] = {0,1,3,2};
        REPEAT_OP(op_D_inv,rotateOrder[findWhite]);

        while(index_of(cube.colors[1],white) != index_of(output.second[1].colors,white))
            DO_OPS(RUR_U_);
    }
    // do bottom layer
    {
        std::vector<float> leftColor  = output.second[1].colors[2];  
        std::vector<float> rightColor = output.second[1].colors[0];

        int rotateOrder[] = {1,0,2,3}; // left and right
        int rotateOrderEdge[] = {2,1,0,3}; // left and right


        bool done;
        int counter = 0;
        do {
            done = true;
            for(int _ = 0; _ < 3; _++) {
                for(int i = 0; i < 4; i++) {
                    if(color_exist(output.second[2*i].colors,white) != -1) {
                        if(color_exist(output.second[2*i].colors,leftColor.data()) != -1) {
                            REPEAT_OP(op_U,rotateOrder[i]);
                            std::vector<std::vector<float>>  tmp = output.second[2].colors;
                            while(index_of(cube.colors[3],white) != index_of(output.second[3].colors,white) || !arr_equal(tmp,output.second[3].colors))  
                                DO_OPS(L_U_LU);
                            // printf("left\n");
                        } else if(color_exist(output.second[2*i].colors,rightColor.data()) != -1) {
                            REPEAT_OP(op_U, rotateOrder[3 -i]);
                            std::vector<std::vector<float>>  tmp = output.second[4].colors;
                            while(index_of(cube.colors[5],white) != index_of(output.second[5].colors,white) || !arr_equal(tmp,output.second[5].colors))  
                                DO_OPS(BUB_U_);
                            // printf("right\n");
                        } else {
                            REPEAT_OP(op_U_inv,rotateOrderEdge[i]);
                            DO_OPS(B_U_BU);
                            // printf("edje\n");
                        }
                    }
                }
            }

            for(int i = 1; i < 4; i++) {
                if(index_of(cube.colors[2 * i + 1],white) != index_of(output.second[2*i+1].colors,white)) {
                    switch (i) {
                        case 1: DO_OPS(L_U_LU); break;
                        case 2: DO_OPS(BUB_U_); break;
                        case 3: DO_OPS(B_U_BU); break;
                        default: printf("This should no be Reached!!!"); break;
                    }
                    done = false;
                    break;
                }
            }



        } while (!done);
    }

    // do top layer poses
    {
        int rotateOrder[] = {0,1,3,2};
        int counter = 0;
        int thatOne = 0; 
        int r = 0;
        bool foundFormation = false;
	    do {
            counter = 0;
            for(int i = 0; i < 4; i++) {
	    	    bool x = true;
                for(auto color: output.second[i * 2].colors) {
                    if(!COLOR_EQUAL(color,yellow)) {
                        if(color_exist(output.second[i*2+1].colors,color.data()) == -1) {
                            x = false;
	    	    	        break;
                        }
                    }
	    	    }
	    	    if(x) {
	    	    	counter++;
                    thatOne = i;
                }
            }
            
            if(counter == 4) {
                break;
            }

            if(!foundFormation && counter != 4) {
    	        if(counter == 1) {
                    REPEAT_OP(op_U_inv,rotateOrder[thatOne]);
                    REPEAT_OP(op_D_inv,rotateOrder[thatOne]);
                    foundFormation = true;
                } else {
                    r = (r + 1) % 4;
                    if(r == 0) {
                        DO_OPS(URU_L_UR_U_L);
                    }
                    DO_OP(op_U);
                }
            } else if(foundFormation) {
                DO_OPS(URU_L_UR_U_L);
            }
            

	    } while(true);

        REPEAT_OP(op_F,2);
        REPEAT_OP(op_B,2);
    }
    
    // do top layer all
    {
        for (auto i : bottomOrder) {
            std::vector<std::vector<float>> tmp = output.second[1].colors;
            while (index_of(cube.colors[1],white) != index_of(output.second[1].colors,yellow) || !arr_equal(tmp,output.second[1].colors) ) {
                DO_OPS(RUR_U_);
            }
            DO_OP(op_D);
        }
    }       
    for(int i = 0; i < ops.size();i++) {
        printf("%d \n",ops[i]);
    }
    return ops;
}

bool BasicSolver::is_solved(std::vector<int> pOrder) {
    printf("re-implemnt basic solver is_solved \n");
    return false;
}

BasicSolver::~BasicSolver(){}



#endif
