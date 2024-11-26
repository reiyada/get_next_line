/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:42 by ryada             #+#    #+#             */
/*   Updated: 2024/11/26 12:05:00 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_current_line(char *str)
{
	char	*current_line;
	int		end;

	if (!str || *str == '\0')
		return (NULL);
	end = ft_find_line_end(str);
	if (end == -1)
		end = ft_strlen(str);
	current_line = (char *)malloc(sizeof(char) * (end + 2));
	if (!current_line)
		return (NULL);
	ft_strlcpy(current_line, str, end + 2);
	return (current_line);
}

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	if (!temp)
	{
		free(text);
		return (NULL);
	}
	free(text);
	return (temp);
}

char	*ft_read_update_remainder(int fd, char *remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	if (!remainder)
	{
		remainder = malloc(sizeof(char));
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		remainder = ft_join_and_free(remainder, buffer);
		if (!remainder)
			return (NULL);
		if (ft_strchr(remainder, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1 || (remainder && *remainder == '\0'))
		return (free(remainder), NULL);
	return (remainder);
}

char	*ft_update_data(char *remainder)
{
	char	*new_remainder;
	int		end;
	size_t	new_len;

	if (!remainder)
		return (NULL);
	end = ft_find_line_end(remainder);
	if (end == -1 || remainder[end + 1] == '\0')
		return (free(remainder), NULL);
	new_len = ft_strlen(remainder) - end;
	new_remainder = malloc(new_len * sizeof(char));
	if (!new_remainder)
		return (free(remainder), NULL);
	ft_strlcpy(new_remainder, &remainder[end + 1], new_len);
	free(remainder);
	if (!*new_remainder)
		return (free(new_remainder), NULL);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = ft_read_update_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	current_line = ft_extract_current_line(remainder);
	remainder = ft_update_data(remainder);
	return (current_line);
}

// read(fd, buffer, BUFFER_SIZE):
//Reads up to BUFFER_SIZE bytes from the file associated
//with the file descriptor fd into the buffer.
//Returns the number of bytes actually read (bytesRead).
//Positive value: Number of bytes successfully read.
//0: End of file (EOF).
//-1: An error occurred.

// STDOUT_FILENO is standard output(write)
// STDIN_FILENO is standard input(write)
// STDERR_FILENO is standard error(write)