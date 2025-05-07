#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS]; // Global variable to store thread IDs

void sigusr1_handler(int signum) { // signal handler
    pthread_t tid = pthread_self();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    fprintf(stdout, "Thread %lu received SIGUSR1 signal (parent=%d) [pid=%d] (tid=%lu)\n", 
            tid, ppid, pid, tid);
}

void *thread_function(void *arg) { // thread function
    signal(SIGUSR1, sigusr1_handler); // <-- Now moved here
    while (1) sleep(1); // Keep the thread alive
    return NULL;
}

int main() {
    // signal(SIGUSR1, sigusr1_handler); // <-- Commented out in main()
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create"); 
            exit(EXIT_FAILURE);
        }
    }
    
    pid_t pid = getpid();
    pid_t ppid = getppid();
    pthread_t main_tid = pthread_self();
    fprintf(stdout, "Parent Process ID: %d, Process ID: %d, main() thread ID: %lu\n",
            ppid, pid, main_tid);
    fprintf(stdout, "Thread IDs: 0=%lu, 1=%lu, 2=%lu and 3=%lu\n",
            threads[0], threads[1], threads[2], threads[3]);
    
    kill(pid, SIGUSR1); // send signal to entire process
    pthread_kill(threads[2], SIGUSR1); // send signal to thread[2]

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join"); 
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
