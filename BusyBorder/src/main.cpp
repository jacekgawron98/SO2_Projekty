#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <atomic>
#include <time.h>
#include <stdlib.h>
#include "helperFunctions.h"
#include "person.h"
#include "checkpoint.h"

Checkpoint* checkpoints;
std::mutex logsMutex;
std::vector<Person> personList;
std::vector<std::thread> threads;
std::condition_variable quarantineCV; 
WINDOW* logswin;
WINDOW* mainwin;
bool priorityFree = true;

bool running = true;
int id = 0;
int threadsCount = 20;

int main(){
    srand(time(NULL));
    int numberOfCheckpoints;
    int startTime;
    int healthTime;
    int quarantineTime;
    int idTime;

    
    std::cout << "Number of checkpoints: ";
    std::cin >> numberOfCheckpoints;

    std::cout << "Initial control time[s]: ";
    std::cin >> startTime;

    std::cout << "Health control time[s]: ";
    std::cin >> healthTime;

    std::cout << "Quarantine time[s]: ";
    std::cin >> quarantineTime;

    std::cout << "Identity control time[s]: ";
    std::cin >> idTime;

    checkpoints = new Checkpoint[numberOfCheckpoints];

    initscr();
    printw("Busy border simulation");
    mainwin = newwin(numberOfCheckpoints*3,200,1,0);
    logswin = newwin(5,100,numberOfCheckpoints*3+2,0);
    
    refresh();
    box(mainwin,0,0);
    wrefresh(mainwin);
    
    for(int i  = 0; i<numberOfCheckpoints; i++){
        checkpoints[i].id = i;
        checkpoints[i].drawCheckpoint(-1,new Person());
    }
    
    for(int i = 0; i < 100; i++){
        Person newPerson = Person(i,startTime,healthTime,quarantineTime,idTime, numberOfCheckpoints, threadsCount);
        personList.push_back(newPerson);
    }
    for(int i = 0; i < 100; i++){
        threads.push_back(personList[i].personThread());
    }


    getch();
    //running = false;

    for(int i = 0; i < personList.size(); i++){
        personList[i].running = false;
    }
    for(int i = 0; i < threads.size(); i++){ 
        threads[i].join();
    }

    endwin();
    return 0;
}