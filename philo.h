

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
struct s_tinfo
{
    pthread_mutex_t mutex;
    int p_id;  
};

typedef struct s_test
{
    int filo_num;
    int x;  
} t_test;

