#include "philosopher.h"
#include "helperFunctions.h"
#include <unistd.h>
#include <iostream>

Philosopher::Philosopher(int id, int sleepTime, int eatTime, int philosophersTotal, sem_t& waiter, sem_t forks[]){
    this->id = id;
    this->sleepTime = sleepTime;
    this->eatTime = eatTime;
    this->eatCounter = 0;
    this->totalNumber = philosophersTotal;
    this->state = "INIT";
    this->waiter = waiter;
    this->forks = forks;
    this->holdsLeft = false;
    this->holdsRight = false;
    running = true;
}

void Philosopher::eat(){
    this->state = "EAT"; 
    int modifier = generateRandomInt(-0.2 * eatTime, 0.2 * eatTime);
    usleep(eatTime+modifier);
    this->eatCounter++;
}

void Philosopher::think(){
    this->state = "THINK";
    int modifier = generateRandomInt(-0.2 * sleepTime, 0.2 * sleepTime);
    usleep(sleepTime+modifier);
}

void Philosopher::execute(){
    while(running){
        think();
        this->state = "HUNGRY";
        sem_wait(&waiter);
        sem_wait(&forks[getLeftFork()]);
        this->holdsLeft = true;
        sem_wait(&forks[getRightFork()]);
        this->holdsRight = true;
        eat();
        sem_post(&forks[getRightFork()]);
        this->holdsRight = false;
        sem_post(&forks[getLeftFork()]);
        this->holdsLeft = false;
        sem_post(&waiter);
    }
}

int Philosopher::getLeftFork(){
    return this->id;
}

int Philosopher::getRightFork(){
    return (this->id +1) % this->totalNumber;
}

int Philosopher::getId(){
    return this->id;
}

int Philosopher::getEatCounter(){
    return this->eatCounter;
}

std::string Philosopher::getState(){
    return this->state;
}

std::thread Philosopher::philospherThread(){
    return std::thread(&Philosopher::execute,this);
}