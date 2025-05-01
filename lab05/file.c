
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024  // Define buffer size

int main() {
    int fd;  // File descriptor
    char buffer[BUFFER_SIZE];

    // Open the file "input.txt" for reading and writing (O_RDWR)
    fd = open("input.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    // Read contents of file into buffer
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(1);
    }

    printf("Parent: Read content from file:\n%.*s\n", (int)bytesRead, buffer);

    // Create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(fd);
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child: Modifying file content...\n");

        // Move file pointer to the beginning before writing
        lseek(fd, 0, SEEK_SET);

        // Write new content to the file
        const char *newContent = "Processed by child process\n";
        ssize_t bytesWritten = write(fd, newContent, sizeof("Processed by child process\n") - 1);
        if (bytesWritten == -1) {
            perror("Error writing to file");
            close(fd);
            exit(1);
        }

        close(fd);  // Close file before executing new process

        // Use execlp() to replace child process with "cat input.txt"
        execlp("cat", "cat", "input.txt", NULL);

        // If execlp fails
        perror("execlp failed");
        exit(1);
    } else {  // Parent process
        wait(NULL);  // Wait for child process to complete
        printf("Parent: Child process completed. Exiting.\n");
    }

    close(fd);  // Close file
    return 0;
}
