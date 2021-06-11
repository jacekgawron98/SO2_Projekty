#ifndef PERSON_H
#define PERSON_H

#include <thread>
#include <mutex>
#include <stdarg.h>

enum PersonState{
    NONE,
    INIT,
    WAIT,
    START_CONTROL,
    HEALTH_CONTROL,
    QUARANTINE,
    ID_CONTROL
};

enum PersonType{
    ENTER,
    EXIT
};

class Person{
    int id;
    int startTime;
    int healthTime;
    int quarantineTime; 
    int idTime;
    int checkpointsLength;
    int threadsCount;
    int checkpointIndex;
    PersonType type;
public:
    PersonState state;
    bool running;

    Person();

    Person(int id, int startTime, int healthTime, int quarantineTime, int idTime, int length, int threadCount);
    
    int claimCheckpoint();

    void execute();
    void initialControl();
    bool healthControl();
    void quarantine();
    bool identityControl();

    void resetThread();

    void drawLogs(char const *log,...);
    
    int getId();

    std::thread personThread();
};

#endif