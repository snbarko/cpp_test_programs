#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <csignal>

int threadno = 0;
pthread_t th1, th2;
int globalstatus = 1;
int th_status = 1;

void func1(int th_nu)
{
    while ( th_status) {
        printf ("Hello all i m #%d thread. I am running at func1. status %d\n", th_nu, threadno);
        sleep(1);
    }
    sleep(5);
    printf ("Gracefully exiting from func1\n");
}

void func2(int th_nu)
{
    while ( th_status) {
        printf ("Hello all i m #%d thread. I am running at func2.status %d\n", th_nu, threadno);
        sleep(1);
    }
    sleep(6);
    printf ("Gracefully exiting from func1\n");
}

void thsignalHandler(int sig_nu)
{
    printf ("Oh no this thread is killed %d\n", threadno);
    th_status = 0;
}

void *thread_routine (void *arg)
{
    int *number = (int *)arg;

    threadno = *number;
    printf ("Thread is %d\n", threadno);

    signal(SIGUSR1, thsignalHandler);

    // If i m 1st thread i m calling function func1
    if (*number == 1)
        func1(*number);
    else
        func2(*number);

    printf ("Exiting thread %d\n", *number);
}

void signalHandler(int signum)
{
    int ret = 0;
    printf("Interrupt signal received\n");
    globalstatus = 0;
    pthread_kill(th1, SIGUSR1);
}

int main()
{
    void *status = NULL;
    int number = 1, num = 2;

    printf("This program will spawn multiple threads and all will be doing some work in parallel\n");

    signal(SIGINT, signalHandler);

    pthread_create(&th1, NULL, thread_routine, &number);
    pthread_create(&th2, NULL, thread_routine, &num);

    while (globalstatus) {
        printf ("This is main thread\n");
        sleep(1);
    }
    pthread_join(th1, &status);
    printf ("Thread 1 returned\n");
    pthread_join(th2, &status);
    printf ("Thread 2 returned\n");
    sleep(2);
    printf ("Exiting main program\n");
    return 0;
}
