#include "philo.h"


long int x = 0;
void *thread(void* arg)
{
    long int i;
    struct s_tinfo *mutexx;

    mutexx = (struct s_tinfo *)arg;

    i = 0;
    pthread_mutex_lock(&mutexx->mutex);
    while (i < 100000000)
    {
        i++;
        x++;
    }
    pthread_mutex_unlock(&mutexx->mutex);    
    return (0);
}
int main()
{
    pthread_t threads;
    pthread_t threads1;
    pthread_mutex_t mutexx;
    struct s_tinfo thread_struct;
    thread_struct.mutex = mutexx;
    pthread_mutex_init(&thread_struct.mutex, NULL);

    pthread_create(&threads, NULL, thread, &thread_struct);
    pthread_create(&threads1, NULL, thread, &thread_struct);
    pthread_join(threads, NULL);
    pthread_join(threads1, NULL);
    
    printf(">>%ld\n", x);
    pthread_mutex_destroy(&mutexx);
    return (0);
}
