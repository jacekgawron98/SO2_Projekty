#ifndef FORK_H
#define FOORK_H

#include <mutex>

struct Fork{
    std::mutex mutex;
};

#endif