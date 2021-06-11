#include "helperFunctions.h"

int generateRandomInt(int min, int max){
    return (rand()%(max+1-min)) + min;
}