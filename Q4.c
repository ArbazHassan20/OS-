#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int in_fd = open("input.txt", O_RDONLY);
    if (in_fd < 0) {
        perror("Error opening input file");
        exit(1);
    }

    int out_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0) {
        perror("Error opening output file");
        close(in_fd);
        exit(1);
    }

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(in_fd, buffer, sizeof(buffer))) > 0) {
        write(out_fd, buffer, bytes);
    }

    close(in_fd);
    close(out_fd);
    printf("File copied successfully.\n");
    return 0;
}
