/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:42 by ryada             #+#    #+#             */
/*   Updated: 2024/11/21 15:33:08 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *stored_data;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read; //bc it can be negative when there is an error
    int newline_start;
    char *current_line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        stored_data = ft_strjoin(stored_data, buffer);
        newline_start = ft_find_new_line(buffer);
        if (newline_start >= 0)
        {
            
        }
        if (buffer == '\n')
            not_printed = buffer;
    }
    
}

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