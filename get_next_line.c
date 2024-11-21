/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:42 by ryada             #+#    #+#             */
/*   Updated: 2024/11/22 00:44:13 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *remained_data;
    char buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read; //bc it can be negative when there is an error
    int line_end;
    char *current_line;
    char *temp;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!remained_data)
    {
        remained_data = (char *)malloc(1);
        if (!remained_data)
            return NULL;
        remained_data[0] = '\0';
    }
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        temp = remained_data;
        remained_data = ft_strjoin(remained_data, buffer);
        free (temp);
        while ((line_end = ft_find_line_end(remained_data)) >= 0)
        {
            current_line = ft_extract_current_line(remained_data, line_end);
            remained_data = ft_update_data(remained_data, line_end);
            return current_line;
        }
    }
    if (bytes_read < 0)
    {
        ft_free_remained_data(&remained_data);
        return NULL;
    }
    if (remained_data && *remained_data)
    {
        current_line = remained_data;
        remained_data = NULL;
        return current_line;
    }
    ft_free_remained_data(&remained_data);
    return NULL;
}

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return 1;
//     }

//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line); // Free the allocated memory after use
//     }

//     close(fd);
//     return 0;
// }

// int main(void)
// {
//     int fd;
//     char buffer[BUFFER_SIZE];
//     ssize_t bytes_read;
//     char *new_line;

//     fd = open("test.txt",O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening the file\n");
//         return (-1);
//     }
//     if ((bytes_read = read(fd, buffer, BUFFER_SIZE) > 0))
//     {
//         new_line = get_next_line(fd);
//         printf("%s\n", new_line);
//         free(new_line);
//     }
//     else if (bytes_read == 0)
//     {
//         printf("The file has been printed successfully!\n");
//     }
//     else
//     {
//         perror("Error reading the file\n");
//         return (-1);
//     }
//     close(fd);
//     return (0);
// }

// read(fd, buffer, BUFFER_SIZE):

//     Reads up to BUFFER_SIZE bytes from the file associated with the file descriptor fd into the buffer.
//     Returns the number of bytes actually read (bytesRead).
//         Positive value: Number of bytes successfully read.
//         0: End of file (EOF).
//         -1: An error occurred.

// STDOUT_FILENO is standard output(write)
// STDIN_FILENO is standard input(write)
// STDERR_FILENO is standard error(write)