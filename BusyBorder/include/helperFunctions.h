#ifndef HELPER_H
#define HELPER_H

#include <time.h>
#include <stdlib.h>
#include <mutex>
#include <condition_variable>
#include <ncurses.h>
#include "checkpoint.h"

extern WINDOW* logswin;
extern WINDOW* mainwin;
extern Checkpoint* checkpoints;
extern std::mutex logsMutex;
extern std::condition_variable quarantineCV; 
extern bool priorityFree;
 
int generateRandomInt(int min, int max);

#endif