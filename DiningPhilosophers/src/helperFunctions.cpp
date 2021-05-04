#include "helperFunctions.h"

int generateRandomInt(int min, int max){
    srand(time(NULL));
    return (rand()%(max+1-min)) + min;
}