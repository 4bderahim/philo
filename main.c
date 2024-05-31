
#include "philo.h"


pthread_mutex_t mutexx;
int x = 0;
void *thread(void* arg)
{
    long int i;
    //struct s_tinfo pth;

    //pth.mutex = *(pthread_mutex_t *)arg;
    
    i = 0;
    while (i < 10000000000)
    {
        pthread_mutex_lock(&mutexx);
        i++;
        x++;
        pthread_mutex_unlock(&mutexx);
    }

    return (arg);
}
int main()
{
    pthread_t threads;
    pthread_t threads1;
    
    struct s_tinfo thread_struct;
   // thread_struct.mutex = mutexx;
    pthread_mutex_init(&mutexx, NULL);
    int t;
    t = 0;
    pthread_create(&threads, NULL, thread, "");
    pthread_create(&threads1, NULL, thread, "");
    pthread_join(threads, NULL);
    //usleep(111000000);
    
    pthread_join(threads1, NULL);
    //     t++;
    // }
    printf(">>%d\n", x);
    pthread_mutex_destroy(&mutexx);
    return (0);
}
