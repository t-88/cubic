#ifndef CUBIC_UTILS_H_
#define CUBIC_UTILS_H_

#include <stdlib.h>
#include <vector>
#include "shared.h"

int color_exist(std::vector<std::vector<float>> colors, float color[]){
    for (size_t i = 0; i < 3; i++)
        if(COLOR_EQUAL(colors[i],color)) return i;
    return -1;
}
// takes cubes and checks if they are the same
bool same_colors(std::vector<std::vector<float>> arr1,std::vector<std::vector<float>> arr2) {
    for (auto c1 : arr1) {
        if(color_exist(arr2,c1.data()) == -1) {
            return false;
        }
    }
    return true;
}
int index_of(std::vector<std::vector<float>> colors, float* color) {
    for(int i = 0; i < 3; i++)
        if(COLOR_EQUAL(colors[i],color))
            return i;
    return -1;
}
#endif