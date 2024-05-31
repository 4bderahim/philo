
#include "philo.h"



int x = 0;

void *thread(void* arg)
{
    long int i;

    i = 0;
    while (i < 10000000000)
    {
        //pthread_mutex_lock()
        i++;
        x++;
    }
    return (arg);
}
int main()
{
    pthread_t threads;
    pthread_t threads1;
    pthread_mutex_t mutex;
    //struct s_tinfo thread_struct;

    //thread_struct.mutex = mutex;

    


    pthread_mutex_ini(&mutex, NULL);

    int t;
    t = 0;
    pthread_create(&threads, NULL, thread, "new thread");
    pthread_join(threads, NULL);
    usleep(111000000);
    pthread_create(&threads1, NULL, thread, "new thread");
    pthread_join(threads1, NULL);
    //     t++;
    // }
    printf(">>%d\n", x);
    //pthread_mutex_destroy(mutex);
    return (0);
}
