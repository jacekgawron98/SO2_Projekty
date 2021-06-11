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
extern WINDOW* totalswin;
extern Checkpoint* checkpoints;
extern std::mutex screenMutex;
extern std::condition_variable quarantineCV; 
extern int enteredTotal;
extern int leftTotal;
extern bool priorityFree;
 
int generateRandomInt(int min, int max);

void refreshTotals();

#endif