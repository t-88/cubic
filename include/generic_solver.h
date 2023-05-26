#ifndef GENERIC_SOLVER
#define GENERIC_SOLVER

#include "cubic.h"
#include "solver.h"


#define MAX_POP 100
#define MUTATION_CHANCE 80





class GenericSolver : Solver
{
private:
    std::array<std::array<Operation,MAX_SOLVE_STEPS>,MAX_POP> pop; 
public:
    Cubic cube;
    bool doneSolving = false;
    std::array<Operation,MAX_SOLVE_STEPS> solvingPop;

    GenericSolver();
    
    std::array<Operation,MAX_SOLVE_STEPS> step(Cubic cube);

    void pop_init();
    void mutaion();
    std::array<std::array<Operation,MAX_SOLVE_STEPS>,MAX_POP>  crossover(std::array<std::array<Operation,MAX_SOLVE_STEPS>,2>);
    std::array<std::array<Operation,MAX_SOLVE_STEPS>,2>  parent_selection();


    std::array<Operation,MAX_SOLVE_STEPS> random_chromo();
    float fitness(std::array<Operation,MAX_SOLVE_STEPS> chromo,Cubic cube);
    bool is_solved(std::vector<int>);
    
    
    ~GenericSolver();
};

GenericSolver::GenericSolver(){
    pop_init();
}


std::array<Operation,MAX_SOLVE_STEPS> GenericSolver::step(Cubic _cube) {
    if(doneSolving) return solvingPop;

    cube = _cube;
    std::array<Operation,MAX_SOLVE_STEPS> ops = {};
    std::array<std::array<Operation,MAX_SOLVE_STEPS>,2> ps = parent_selection();
    if(doneSolving) {
        return solvingPop; 
    }
    pop = crossover(ps);
    mutaion();    



    return ops;
}

std::array<Operation,MAX_SOLVE_STEPS> GenericSolver::random_chromo()  {
    
    std::array<Operation,MAX_SOLVE_STEPS> chromo; 
    for(int i = 0; i < MAX_SOLVE_STEPS; i++)
        chromo[i] = ops[rand() % 12];
    return chromo;
}
void GenericSolver::pop_init() {
    for(int i = 0; i < MAX_POP ; i++) {
        pop[i] = random_chromo();
    }
}
void GenericSolver::mutaion() {
    for(int i = 0 ; i < MAX_POP; i++) {
        if(rand() % 100 < MUTATION_CHANCE) {
            pop[i][rand() % MAX_SOLVE_STEPS] = ops[rand() % 12];    
        } 
    }
}

std::array<std::array<Operation,MAX_SOLVE_STEPS>,MAX_POP>  GenericSolver::crossover(std::array<std::array<Operation,MAX_SOLVE_STEPS>,2> ps) {
    std::array<std::array<Operation,MAX_SOLVE_STEPS>,MAX_POP> newPop;
    for(int i = 0 ; i < MAX_POP; i++) {
        std::array<Operation,MAX_SOLVE_STEPS> ops;
        int r = rand() % MAX_SOLVE_STEPS;
        for(int y = 0; y < MAX_SOLVE_STEPS; y++) {
            if(r <= y) 
                ops[y] =  ps[0][y];
            else 
                ops[y] = ps[1][y];
        }
        newPop[i] = ops; 
    } 
    return newPop;
}
std::array<std::array<Operation,MAX_SOLVE_STEPS>,2>  GenericSolver::parent_selection() {
    std::vector<std::pair<int , float>> popFit;

    for(int i = 0 ; i < MAX_POP;i++) {
        std::pair<int , float> pair;
        pair.first = i;
        pair.second = fitness(pop[i], cube); 
        popFit.push_back(pair);    
        printf("index: %d fit: %f ",i,pair.second);
        for(int j = 0; j < MAX_SOLVE_STEPS; j++) {
            printf("%d ",pop[pair.first][j]);
        }
        printf("\n");

        
        if(doneSolving) break;
    }
    if(doneSolving) {
        solvingPop = pop[popFit[popFit.size() - 1].first]; 
        return std::array<std::array<Operation,MAX_SOLVE_STEPS>,2> {
            pop[popFit[0].first],
            pop[popFit[0].first],
        };
    }  

    std::sort(
        popFit.begin(),
        popFit.end(),
        [] (std::pair<int ,float> a , std::pair<int ,float> b) {return a.second > b.second; }
    );

    return std::array<std::array<Operation,MAX_SOLVE_STEPS>,2> {
        pop[popFit[0].first],
        pop[popFit[1].first]
    };
}

float GenericSolver::fitness(std::array<Operation,MAX_SOLVE_STEPS> chromo,Cubic cube) {
    std::vector<int> newOrder = cube.order;
    for(auto op : chromo) {
        newOrder = cube.do_op(op,newOrder);

        if(is_solved(newOrder)) {
            doneSolving = true;
            break;
        }
   
    }
    if(doneSolving)
        return 10000000;


    float f = 0;
    for(int i = 0; i < newOrder.size(); i++) {
        if(newOrder[i] == order[i])
            f += 2;
        else
            f -= 1;
        if(rotationsX[newOrder[i]] == rotationsX[order[i]]) 
            f += 2;
        else
            f -= 1;
    }
    return f;
}
bool GenericSolver::is_solved(std::vector<int> pOrder) {
    for(int i = 0; i < pOrder.size() ; i++)
        if((pOrder[i] != order[i]) || (rotationsX[pOrder[i]] != rotationsX[order[i]])) return false;
    return true;

}

GenericSolver::~GenericSolver(){}



#endif