#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <mutex>
#include <condition_variable>
#include <ncurses.h>
#include <vector>
#include "person.h"

class Checkpoint{
public:
    int id;
    std::mutex checkpointMutex;
    std::condition_variable checkpointQuarantine;
    bool priorityFree;
    Person* activePerson;
    Person* quarantinePerson;
    std::vector<int> quarantineIDs;

    Checkpoint();

    void drawCheckpoint(int quarantineID,Person* p);

    void addToQuarantine(int id);
    void removeFromQuarantine(int id);
};

#endif