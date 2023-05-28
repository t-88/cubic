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



class BasicSolver : Solver
{
private:
public:
    Cubic cube;
    bool doneSolving = false;
    std::array<Operation,MAX_SOLVE_STEPS> solvingPop;
    std::vector<int> _pOrder;
    std::pair<std::vector<int>,std::vector<Cube>> output;

    BasicSolver();
    
    std::array<Operation,MAX_SOLVE_STEPS> step(Cubic cube);
    bool is_combatable(std::vector<Cube>, int , int,int*);
    int color_exist(std::vector<Cube> , int, float color[]);

    bool is_solved(std::vector<int>);
    ~BasicSolver();
};

BasicSolver::BasicSolver(){}
int BasicSolver::color_exist(std::vector<Cube> cubes, int index, float color[]){
    for (size_t i = 0; i < 3; i++)
        if(COLOR_EQUAL(cubes[index].colors[i],color)) return i;

    return -1;
}
bool BasicSolver::is_combatable(std::vector<Cube> cubes, int i1, int i2,int* compPos) {
    for(int i = 0; i < 3 ; i++){
        int face = color_exist(cubes,i1,cubes[i2].colors[i].data());
        if(!COLOR_EQUAL(cubes[i2].colors[i],white) &&  face !=  -1) {
            
            // printf("p=>>>>>>>> %d %d\n",face,i);
            // printf("------------------\n");
            // PRINT_COLOR(cubes[i1].colors[face]);
            // PRINT_COLOR(cubes[i2].colors[i]);
            // printf("------------------\n");
            
            *compPos = face;


            return true; 
        }
    }

    return false;
}

std::array<Operation,MAX_SOLVE_STEPS> BasicSolver::step(Cubic cube) {
    std::array<Operation,MAX_SOLVE_STEPS> ops = {};
    output.first =  cube.order;
    output.second =  cube.cubes;


    int i = 0;
    int bestPossible = 0;
    int ibestPossible  = 0;



    int foundPerfect = 0;
    int found = 0;
    float white[3] = WHITE;
    for(i = 0 ; i < 4; i++)
        if(output.first[2 * i + 1] % 2 == 1) {
            found = 1;
            bestPossible = output.first[2 * i + 1]; // pos is right but rotation is wrong
            ibestPossible = 2 * i + 1;
            break;                
        }

    // if found prefect one  
    // if found one  
    // if its on top
    printf("\n");

#if 0 
    // we get out with a prefect state one prefect rotated piece in 1 or 3 
    
    if(found) {
        PRINT_SOLVE_STEP_ARGS("found with rotation %d %d\n",bestPossible,ibestPossible);
        if(bestPossible != 1 && bestPossible != 3) {
            int offset = bestPossible == 5  ? 3 : 1;
            Operation op = bestPossible == 5 ? op_D_inv : op_D;
            int opTimes = 2;
            bestPossible = offset;
            for(int i = 0 ; i < opTimes; i++) {
                pOrder = cube.do_op(op,pOrder);
                PRINT_SOLVE_STEP(op == op_D ? "D " : "D_inv ");
            }
        }

        int j = bestPossible == 1 ? 1 : 0;
        foundPerfect = cube.colors[ibestPossible][j][0] == white[0] &&
                    cube.colors[ibestPossible][j][1] == white[1] &&
                    cube.colors[ibestPossible][j][2] == white[2];

        PRINT_SOLVE_STEP_ARGS("is a prefect match %d\n",foundPerfect);
        if(!foundPerfect) {
            PRINT_SOLVE_STEP("\n");
            if(bestPossible == 1 || bestPossible == 5) {
                PRINT_SOLVE_STEP("R ");
                PRINT_SOLVE_STEP("U_inv ");
                PRINT_SOLVE_STEP("R_inv ");
                PRINT_SOLVE_STEP("R_inv ");
                pOrder = cube.do_op(op_R,pOrder);
                pOrder = cube.do_op(op_U_inv,pOrder);
                pOrder = cube.do_op(op_R_inv,pOrder);
                pOrder = cube.do_op(op_R_inv,pOrder);
            } else {
                PRINT_SOLVE_STEP("L_inv ");
                PRINT_SOLVE_STEP("U ");
                PRINT_SOLVE_STEP("L ");
                PRINT_SOLVE_STEP("L ");

                pOrder = cube.do_op(op_L_inv,pOrder);
                pOrder = cube.do_op(op_U,pOrder);
                pOrder = cube.do_op(op_L,pOrder);
                pOrder = cube.do_op(op_L,pOrder);
            }
            PRINT_SOLVE_STEP("\n");
        }
    }
#endif

    int bottomOrder[] = {1,3,7,5};
    int compPos = 0;
    PRINT_SOLVE_STEP_ARGS("found: %d\n",bestPossible);
    for(int j = 0; j < 4; j++) {

    for(int i = 0; i < 4; i++) {
        if(color_exist(output.second,2*i,white) != -1) {

            if(is_combatable(output.second,bestPossible,2 * i,&compPos)) {
                PRINT_SOLVE_STEP_ARGS("found combatable %d %d\n",2 * i,compPos);
                if(compPos == 2) {
                    // printf("asdasd %d\n",color_exist(output.second,2*i,white));
                    // PRINT_COLORS(output.second[2*i].colors);
                    // printf("asdasd\n");
                    int mappedOps[] = {1,0,2,3};
                    for(int j = 0; j < mappedOps[i]; j++) {
                        output = cube.do_op(op_U,output);
                        PRINT_SOLVE_STEP("U ");
                    }   
                    PRINT_SOLVE_STEP("\n");

                    Operation ops[] = {op_L_inv,op_U_inv,op_L,op_U};
                    auto tmp = output.second[2].colors; 
                    PRINT_COLORS(tmp);
                    PRINT_COLORS(output.second[3].colors);
                    while (
                           !COLOR_EQUAL(output.second[3].colors[0] , tmp[1].data()) || 
                           !COLOR_EQUAL(output.second[3].colors[1] , tmp[2].data()) ||  
                           !COLOR_EQUAL(output.second[3].colors[2] , tmp[0].data())   
                    ) {
                        for(auto op: ops) {
                            output = cube.do_op(op,output);
                            PRINT_OP(op);
                        }
                    }
                } else {
                    int mappedOps[] = {1,2,0,3};
                    for(int j = 0; j < mappedOps[i]; j++) {
                        output = cube.do_op(op_U_inv,output);
                        PRINT_SOLVE_STEP("U_inv ");
                    }   
                    PRINT_SOLVE_STEP("\n");

                    Operation ops[] = {op_B,op_U,op_B_inv,op_U_inv};
                    auto tmp = output.second[4].colors; 
                    // PRINT_COLORS(tmp);
                    // PRINT_COLORS(output.second[5].colors);
                    int a = 0;

                    #if 1
                    while (
                           !COLOR_EQUAL(output.second[5].colors[2] , tmp[2].data()) || 
                           !COLOR_EQUAL(output.second[5].colors[0] , tmp[0].data()) ||  
                           !COLOR_EQUAL(output.second[5].colors[1] , tmp[1].data())   
                            ) {
                        for(auto op: ops) {
                            output = cube.do_op(op,output);
                            PRINT_OP(op);
                        }
                        if(a == 10) break;
                        a++;
                    }
                    #endif



                }
            } else {
                PRINT_SOLVE_STEP_ARGS("not combatable %d %d\n",2 * i,compPos);
                int mappedOps[] = {2,1,3,0};
                for(int j = 0; j < mappedOps[i]; j++) {
                    output = cube.do_op(op_U_inv,output);
                    PRINT_OP(op_U_inv);
                }

                Operation ops[] = {op_B_inv,op_U_inv,op_B,op_U};
                auto tmp = output.second[6].colors; 
                // PRINT_COLORS(tmp);
                // PRINT_COLORS(output.second[7].colors);
                while (
                       !COLOR_EQUAL(output.second[7].colors[2] , tmp[2].data()) || 
                       !COLOR_EQUAL(output.second[7].colors[1] , tmp[1].data()) ||  
                       !COLOR_EQUAL(output.second[7].colors[0] , tmp[0].data())   
                        ) {
                    for(auto op: ops) {
                        output = cube.do_op(op,output);
                        PRINT_OP(op);
                    }
                }                

            }
        }
    }
    }




    return ops;
}

bool BasicSolver::is_solved(std::vector<int> pOrder) {
    printf("re-implemnt basic solver is_solved \n");
    return false;
}

BasicSolver::~BasicSolver(){}



#endif