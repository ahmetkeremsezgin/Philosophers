#include <sys/time.h>

unsigned long get_current_time()
{
    struct timeval time;

    gettimeofday(&time, 0);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

