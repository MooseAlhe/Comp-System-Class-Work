#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void sig_handler1(int);
void sig_handler2(int);
void sig_handler3(int);
void sig_handler4(int);
void* thread_func();

int main(int argc, char ** argv)
{
    pthread_t tid[4]; // 4 thread teams
    pthread_attr_t attr1, attr2, attr3, attr4;
    sigset_t set1, set2, set3, set4;


    //Team 1
    signal(SIGHUP,sig_handler1);
    signal(SIGINT,sig_handler1);
    signal(SIGILL,sig_handler1);

    //Team 2
    signal(SIGCHLD,sig_handler2);
    signal(SIGSEGV,sig_handler2);
    signal(SIGFPE,sig_handler2);

    //Team 3
    signal(SIGHUP,sig_handler3);
    signal(SIGTSTP,sig_handler3);
    signal(SIGINT,sig_handler3);

    //Team 4
    signal(SIGABRT,sig_handler4);
    signal(SIGILL,sig_handler4);
    signal(SIGCHLD,sig_handler4);


    // Creates a set of signals to block for team 1 and creates the thread
    sigemptyset(&set1);
    sigaddset(&set1,SIGCHLD);
    sigaddset(&set1,SIGSEGV);
    sigaddset(&set1,SIGFPE);
    sigaddset(&set1,SIGABRT);
    sigaddset(&set1,SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set1,NULL);
    pthread_attr_init(&attr1);
    pthread_create(&tid[0],&attr1,(void*) thread_func,NULL);
    pthread_sigmask(SIG_UNBLOCK, &set1, NULL);


    // Creates a set of signals to block for team 2 and creates the thread
    sigemptyset(&set2);
    sigaddset(&set2,SIGINT);
    sigaddset(&set2,SIGABRT);
    sigaddset(&set2,SIGILL);
    sigaddset(&set2,SIGHUP);
    sigaddset(&set2,SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set2,NULL);
    pthread_attr_init(&attr2);
    pthread_create(&tid[1],&attr2,(void*) thread_func,NULL);
    pthread_sigmask(SIG_UNBLOCK, &set2, NULL);


    // Creates a set of signals to block for team 3 and creates the thread
    sigemptyset(&set3);
    sigaddset(&set3,SIGSEGV);
    sigaddset(&set3,SIGABRT);
    sigaddset(&set3,SIGILL);
    sigaddset(&set3,SIGCHLD);
    sigaddset(&set3,SIGFPE);
    pthread_sigmask(SIG_BLOCK, &set3,NULL);
    pthread_attr_init(&attr3);
    pthread_create(&tid[2],&attr3,(void*) thread_func,NULL);
    pthread_sigmask(SIG_UNBLOCK, &set3, NULL);


    // Creates a set of signals to block for team 4 and creates the thread
    sigemptyset(&set4);
    sigaddset(&set4,SIGINT);
    sigaddset(&set4,SIGSEGV);
    sigaddset(&set4,SIGFPE);
    sigaddset(&set4,SIGHUP);
    sigaddset(&set4,SIGTSTP);
    pthread_sigmask(SIG_BLOCK, &set4,NULL);
    pthread_attr_init(&attr4);
    pthread_create(&tid[3],&attr4,(void*) thread_func,NULL);
    pthread_sigmask(SIG_UNBLOCK, &set4, NULL);


    // send signals to thread
    sleep(1);
    pthread_kill(tid[0],SIGHUP);
    pthread_kill(tid[1],SIGCHLD);
    pthread_kill(tid[2],SIGTSTP);

   

    // closes each thread
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    return 0;
}
void sig_handler1(int sig)    
{
    fprintf(stdout,"Thread %d caught signal number %d\n",(int)pthread_self(),sig);
}
void sig_handler2(int sig)    
{
    fprintf(stdout,"Thread %d caught signal number %d\n",(int)pthread_self(),sig);
}
void sig_handler3(int sig)    
{
    fprintf(stdout,"Thread %d caught signal number %d\n",(int)pthread_self(),sig);
}
void sig_handler4(int sig)    
{
    fprintf(stdout,"Thread %d caught signal number %d\n",(int)pthread_self(),sig);
}

void* thread_func()
{
    fprintf(stdout, "Thread %d created\n",(int)pthread_self());
    sleep(2);
}


