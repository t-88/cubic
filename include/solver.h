#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <set>
#include "shared.h"

enum state {
    three_white,
    solve_white,
};

class Solver
{
private:
    state currS = three_white; 
public:
    std::vector<int> order = {0,1,2,3,4,5,6,7};


    explicit Solver(std::vector<int>);
    explicit Solver();

    std::vector<Operation> step(std::vector<int>);

    ~Solver();

};

Solver::Solver(){

}

std::vector<Operation> Solver::step(std::vector<int> pOrder) {
    std::vector<Operation> ops = {};
    
    
    // three whites step, i put three white peices at bottom and do algorthim
    // {1,3,5,7} that what i want, its array of odd numbers so i use it to my adv and use the rotations 
    // to select the stuff
    std::vector<int> whites = {
        pOrder[1] % 2 && rotationsX[pOrder[1]] == rotationsX[1] ,
        pOrder[3] % 2 && rotationsX[pOrder[3]] == rotationsX[3] ,
        pOrder[5] % 2 && rotationsX[pOrder[5]] == rotationsX[5] ,
        pOrder[7] % 2 && rotationsX[pOrder[7]] == rotationsX[7] ,
    };
    
    int n = std::count (whites.begin(), whites.end(), 1);

    if(n < 3) {
        printf("count: %d \n",n);

        std::vector<int> indexes;
        std::vector<int> poses;
        for(int i = 0; i < 3; i++) 
            if(whites[i] == 0) 
                indexes.push_back(2 * i + 1);
        
        for(int index : indexes) {

            printf("%d %d %f %f\n",index,pOrder[index],rotationsX[pOrder[index]],rotationsX[index]);
        }
    }
    return ops; 
}

Solver::~Solver()
{
}

#endif