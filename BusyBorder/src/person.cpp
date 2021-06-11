#include "person.h"
#include "helperFunctions.h"
#include <unistd.h>
#include <ncurses.h>

Person::Person(){
    this->state = NONE;
}

Person::Person(int id, int startTime,int healthTime, int quarantineTime, int idTime,int length, int threadsCount){
    this->id = id;
    this->threadsCount = threadsCount;
    this->startTime = startTime;
    this->healthTime = healthTime;
    this->quarantineTime = quarantineTime;
    this->idTime = idTime;
    this->checkpointsLength = length;
    this->state = INIT;
    this->type = ENTER;
    running = true;
}

int Person::getId(){
    return this->id;
}

void Person::execute(){
    while(running){
        this->checkpointIndex = claimCheckpoint();
        drawLogs("Waiting %d", this->id);
        std::unique_lock<std::mutex> uniqlock(checkpoints[checkpointIndex].checkpointMutex);
        checkpoints[checkpointIndex].checkpointQuarantine
            .wait(uniqlock,[this]{return checkpoints[checkpointIndex].priorityFree;});
        drawLogs("Person %d entering checkpoint %d", this->id, this->checkpointIndex );
        if(this->type == EXIT){
            if(!identityControl()){
                uniqlock.unlock();
                resetThread();
                continue;
            }
            initialControl();
        }else if(this->type == ENTER){
            initialControl();
            if(!healthControl()){
                uniqlock.unlock();
                checkpoints[checkpointIndex].addToQuarantine(this->id);
                quarantine();
                checkpoints[checkpointIndex].priorityFree = false;
                uniqlock.lock();
                checkpoints[checkpointIndex].priorityFree = true;
            }
            if(!identityControl()){
                checkpoints[checkpointIndex].checkpointQuarantine.notify_all();
                uniqlock.unlock();
                resetThread();
                continue;
            }
        }
        checkpoints[checkpointIndex].checkpointQuarantine.notify_all();
        uniqlock.unlock();
        drawLogs("Person %d unlocked", this->id );
        checkpoints[checkpointIndex].drawCheckpoint(-1,new Person());
        resetThread();
    }
}

int Person::claimCheckpoint(){
    return generateRandomInt(0,this->checkpointsLength);
}

void Person::initialControl(){
    this->state = START_CONTROL;
    std::this_thread::sleep_for(std::chrono::seconds(this->startTime));
    drawLogs("Person %d passed initial control", this->id );
}

bool Person::healthControl(){
    this->state = HEALTH_CONTROL;
    std::this_thread::sleep_for(std::chrono::seconds(this->healthTime));
    int virusRandom = generateRandomInt(0,500);
    if(virusRandom > 200){
        drawLogs("Person %d has a deadly virus", this->id );
        return false;
    }
    drawLogs("Person %d passed health control", this->id );
    return true;
}

bool Person::identityControl(){
    this->state = ID_CONTROL;
    std::this_thread::sleep_for(std::chrono::seconds(this->idTime));
    int criminalRandom = generateRandomInt(0,1000);
    if(criminalRandom > 500){
        drawLogs("Person %d is a wanted criminal", this->id );
        return false;
    }
    drawLogs("Person %d passed identity control", this->id );
    return true;
}

void Person::quarantine(){
    std::this_thread::sleep_for(std::chrono::seconds(this->quarantineTime));
    checkpoints[checkpointIndex].removeFromQuarantine(this->id);
    drawLogs("Person %d finished quarantine", this->id );
}

void Person::drawLogs(char const *log,...){
    char dest[1024 * 16];
    va_list args;
    va_start(args, log);
    vsprintf(dest, log, args);
    va_end(args);
    logsMutex.lock();
    box(logswin,0,0);
    mvwprintw(logswin,2,2,"                                      ");
    mvwprintw(logswin,2,2,dest);
    wrefresh(logswin);
    checkpoints[checkpointIndex].drawCheckpoint(this->id,this);
    wrefresh(mainwin);
    logsMutex.unlock();
}

void Person::resetThread(){
    int nextType = generateRandomInt(0,1);
    if(nextType == 0)
        this->type =  ENTER;
    else if(nextType == 1)
        this->type = EXIT;
    this->id = this->id + this->threadsCount;
    this->state = INIT;
    std::this_thread::sleep_for(std::chrono::seconds(120));
}

std::thread Person::personThread(){
    return std::thread(&Person::execute,this);
}