#ifndef CUBIC_BASIC_SOLVER_H_
#define CUBIC_BASIC_SOLVER_H_
#include <algorithm>

#include "cubic.h"
#include "solver.h"
#include "utils.h"


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
    std::vector<Operation> ooga_booga_solve(Cubic cube);
    ~BasicSolver();
};

BasicSolver::BasicSolver(){}




std::vector<Operation> BasicSolver::ooga_booga_solve(Cubic cube) {
    std::vector<Operation> ops;
    output.first =  cube.order;
    output.second =  cube.cubes;

    int topOrder   []= {0,2,6,4};
    int bottomOrder[] = {1,3,7,5};






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
                            while(index_of(cube.colors[3],white) != index_of(output.second[3].colors,white) || !same_colors(tmp,output.second[3].colors))  
                                DO_OPS(L_U_LU);
                            // printf("left\n");
                        } else if(color_exist(output.second[2*i].colors,rightColor.data()) != -1) {
                            REPEAT_OP(op_U, rotateOrder[3 -i]);
                            std::vector<std::vector<float>>  tmp = output.second[4].colors;
                            while(index_of(cube.colors[5],white) != index_of(output.second[5].colors,white) || !same_colors(tmp,output.second[5].colors))  
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
            while (index_of(cube.colors[1],white) != index_of(output.second[1].colors,yellow) || !same_colors(tmp,output.second[1].colors) ) {
                DO_OPS(RUR_U_);
            }
            DO_OP(op_D);
        }
    }       

    return ops;
}

BasicSolver::~BasicSolver(){}



#endif // CUBIC_BASIC_SOLVER_H_
