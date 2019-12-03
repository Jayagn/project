/*
#include <iostream>
#include <pthread.h>
#include <vector>
#include <time.h>

typedef struct _thread_data {
    int num;
    std::vector<int> intVertices;
} thread_data;

void *thr_func(void *arg) {
    thread_data *data = (thread_data *)arg;
    std::cout << "data received and num is: " << data->num << std::endl;

    for (unsigned i = 0; i < data->intVertices.size(); i++) {
        std::cout << data->intVertices[i] << std::endl;
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{

   pthread_t thr1;
   pthread_t thr2;
   clockid_t cid;

   thread_data thr_data1;
   thread_data thr_data2;

   std::vector<int> vertices{1,2,3,4};

   thr_data1.num = 0;
   thr_data1.intVertices = vertices;

   thr_data2.num = 2;
   thr_data2.intVertices = vertices;


   pthread_create(&thr1, NULL, thr_func, &thr_data1);
   pthread_create(&thr2, NULL, thr_func, &thr_data2);

   int s = pthread_getcpuclockid(pthread_self(), &cid);
   // int s1 = pthread_getcpuclockid(thr1, &cid);
   std::cout << "result of s for th1 is: " << s1 << std::endl;

   pthread_join(thr1, NULL);
   pthread_join(thr2, NULL);


    return 0;
}
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void *thread_start(void *arg)
{
    printf("Subthread starting infinite loop\n");
    for (;;)
        continue;
}

static void pclock(char *msg, clockid_t cid)
{
    struct timespec ts;

    printf("%s", msg);
    if (clock_gettime(cid, &ts) == -1)
        handle_error("clock_gettime");
    printf("%4ld.%03ld\n", ts.tv_sec, ts.tv_nsec / 1000000);
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    clockid_t cid;
    int j, s;

    s = pthread_create(&thread, NULL, thread_start, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");
    /*
    printf("Main thread sleeping\n");
    sleep(1);

    printf("Main thread consuming some CPU time...\n");
    for (j = 0; j < 2000000; j++)
        getppid();

    pclock("Process total CPU time: ", CLOCK_PROCESS_CPUTIME_ID);

    s = pthread_getcpuclockid(pthread_self(), &cid);
    if (s != 0)
        handle_error_en(s, "pthread_getcpuclockid");
    pclock("Main thread CPU time:   ", cid);

    */
    s = pthread_getcpuclockid(thread, &cid);
    if (s != 0)
        handle_error_en(s, "pthread_getcpuclockid");
    pclock("Subthread CPU time: 1    ", cid);
    std::cout << "subthread cid is: " << cid << std::endl;
    exit(EXIT_SUCCESS);
}


