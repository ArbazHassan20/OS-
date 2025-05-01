#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
    printf("\nAlarm received. Exiting...\n");
    exit(0);
}

int main() {
    signal(SIGALRM, alarm_handler);
    alarm(5);

    for (int i = 0; i < 10; i++) {
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}
