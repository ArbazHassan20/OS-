
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // Get user input in parent process
    printf("Enter a message: ");
    fgets(write_msg, BUFFER_SIZE, stdin);
    write_msg[strcspn(write_msg, "\n")] = '\0'; 

    if (pipe(fd) == -1) { // create pipe
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    pid = fork(); // create a child process

    if (pid < 0) { // error occurred
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (pid > 0) { // parent process
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        close(fd[READ_END]); // close unused read end
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1); // write to pipe
        close(fd[WRITE_END]); // close write end
    } 
    else { // child processs
        close(fd[WRITE_END]); // close unused write end
        read(fd[READ_END], read_msg, BUFFER_SIZE); // read from the pipe
        printf("Read: %s\n", read_msg); // print the received message
        close(fd[READ_END]); // close read end
    }

    return 0;
}
