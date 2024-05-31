

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct s_tinfo
{
    pthread_mutex_t mutex;
};