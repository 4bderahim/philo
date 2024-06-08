
#include "philo.h"

void routine (void *arg)
{
    

}

int main ()
{
    pthread_t thread;
    pthread_t thread2;
    pthread_t thread3;

    pthread_mutex_t mut;

    pthread_create(&thread, NULL, routine, NULL);
}