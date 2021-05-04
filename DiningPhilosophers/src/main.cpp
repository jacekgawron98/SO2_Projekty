
#include <vector>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <thread>
#include <string>
#include "philosopher.h"
#include "helperFunctions.h"

std::vector<Philosopher> philosophers;
sem_t* forks;
sem_t waiter;
bool running = true;

void writeTableInfo(){
    std::string leftFork;
    std::string rightFork;
    while(running){
        usleep(1000000);
        for(int i = 0; i<philosophers.size(); i++){
            leftFork = philosophers[i].holdsLeft? "Holds left" : "";
            rightFork = philosophers[i].holdsRight? "Holds right" : ""; 
            std::cout << "Philosopher " << philosophers[i].getId()
                << " | Eat count: " << philosophers[i].getEatCounter()
                << " | State: " << philosophers[i].getState()
                << " | " << leftFork << " " << rightFork << "\n";
        }
        std::cout << "\n";
    }
}

int main(){
    int numberOfPhilosophers;
    int thinkTime;
    int eatTime;
    std::vector<std::thread> threads;

    std::cout << "Number of philosophers: ";
    std::cin >> numberOfPhilosophers;

    std::cout << "Think time[s]: ";
    std::cin >> thinkTime;

    std::cout << "Eat time[s]: ";
    std::cin >> eatTime;

    if(sem_init(&waiter,0,numberOfPhilosophers-1)){
        std::cout << "Sem init error";
        exit(EXIT_FAILURE);
    }

    forks = new sem_t[numberOfPhilosophers];
    for(int i = 0; i < numberOfPhilosophers; i++){
        if(sem_init(&forks[i],0,1)){
            std::cout << "Sem init error";
            exit(EXIT_FAILURE);
        }
    }

    for(int i  = 0; i < numberOfPhilosophers; i++){
        Philosopher p = Philosopher(i, thinkTime * 1000000, 
            eatTime * 1000000,numberOfPhilosophers, waiter, forks);
        philosophers.push_back(p);
    }

    for(int i = 0; i < numberOfPhilosophers; i++){
        threads.push_back(philosophers[i].philospherThread());
    }

    std::thread writer = std::thread(writeTableInfo);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    running = false;
    for(int i = 0; i <threads.size(); i++){
        philosophers[i].running = false;
    }

    for(int i = 0; i <threads.size(); i++){ 
        threads[i].join();
    }
    writer.join();

    return 0;
}