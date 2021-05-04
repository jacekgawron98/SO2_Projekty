#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <string>
#include <thread>
#include <semaphore.h>

enum PhilosopherState{
    INIT,
    THINK,
    HUNGRY,
    EAT
};

class Philosopher{
    int id;
    int sleepTime;
    int eatTime;
    int eatCounter;
    int totalNumber;
    std::string state;
    sem_t waiter;
    sem_t* forks;
public:
    bool running;
    bool holdsLeft;
    bool holdsRight;
    Philosopher(int id, int sleepTime, int eatTime, int philosopherTotal, sem_t& waiter, sem_t forks[]);

    void execute();
    void eat();
    void think();

    int getLeftFork();
    int getRightFork();

    int getId();
    int getEatCounter();
    std::string getState();
    std::thread philospherThread();
};

#endif