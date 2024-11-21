#include "get_next_line.h"
#define BUFFER_SIZE 42

int main(void)
{
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    fd = open("test.txt",O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (-1);
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
        write (STDOUT_FILENO, buffer, bytes_read);
    if (bytes_read == -1)
    {
        perror("Error reading file");
        close(fd);
        return (-1);
    }
    close(fd);
    printf("\nFile closed successfully.\n");
    return (0);
}

// read(fd, buffer, BUFFER_SIZE):

//     Reads up to BUFFER_SIZE bytes from the file associated with the file descriptor fd into the buffer.
//     Returns the number of bytes actually read (bytesRead).
//         Positive value: Number of bytes successfully read.
//         0: End of file (EOF).
//         -1: An error occurred.

// STDOUT_FILENO is standard output(write)
// STDIN_FILENO is standard input(write)
// STDERR_FILENO is standard error(write)