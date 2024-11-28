/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:26:11 by ryada             #+#    #+#             */
/*   Updated: 2024/11/28 11:14:38 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_and_update_remainder(int fd, char *remainder, char *buffer)
{
	int		bytes_read;
	char	*temp;

	temp = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(remainder, buffer);
		if (!temp)
			return (free(remainder), NULL);
		free(remainder);
		remainder = temp;
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	if (bytes_read < 0)
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);
}

char	*ft_extract_line_from_remainder(char **remainder)
{
	char	*line;
	char	*newline_ptr;
	char	*temp;
	size_t	line_length;

	newline_ptr = ft_strchr(*remainder, '\n');
	if (!newline_ptr)
		return (NULL);
	line_length = newline_ptr - *remainder + 1;
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *remainder, line_length + 1);
	temp = ft_strdup(newline_ptr + 1);
	if (!temp)
		return (free(line), NULL);
	free(*remainder);
	*remainder = temp;
	if ((*remainder)[0] == '\0')
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (line);
}

char	*ft_finalize_line(char **remainder, char *buffer)
{
	char	*line;

	if (*remainder && **remainder)
	{
		line = ft_strdup(*remainder);
		if (!line)
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		line = NULL;
	free(*remainder);
	*remainder = NULL;
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!remainder[fd])
	{
		remainder[fd] = ft_strdup("");
		if (!remainder[fd])
			return (free(buffer), NULL);
	}
	remainder[fd] = ft_read_and_update_remainder(fd, remainder[fd], buffer);
	if (!remainder[fd])
		return (free(buffer), NULL);
	line = ft_extract_line_from_remainder(&remainder[fd]);
	if (line)
		return (free(buffer), line);
	return (ft_finalize_line(&remainder[fd], buffer));
}

// int main(int argc, char **argv)
// {
// 	int		fd1, fd2, fd3;
// 	char	*line1, *line2, *line3;
// 	int		i;

// 	if (argc == 4)
// 	{
// 		fd1 = open(argv[1], O_RDONLY);
// 		fd2 = open(argv[2], O_RDONLY);
// 		fd3 = open(argv[3], O_RDONLY);

// 		if (fd1 < 0 || fd2 < 0 || fd3 < 0)
// 		{
// 			perror("Error opening files");
// 			if (fd1 >= 0) close(fd1);
// 			if (fd2 >= 0) close(fd2);
// 			if (fd3 >= 0) close(fd3);
// 			return (1);
// 		}
// 		i = 1;
// 		while (1)
// 		{
// 			line1 = get_next_line(fd1);
// 			line2 = get_next_line(fd2);
// 			line3 = get_next_line(fd3);

// 			if (!line1 && !line2 && !line3)
// 				break;
// 			if (line1)
// 			{
// 				printf("File 1, Line %d: %s", i, line1);
// 				if (line1[ft_strlen(line1) - 1] != '\n')
// 					printf("\n");
// 				free(line1);
// 			}
// 			if (line2)
// 			{
// 				printf("File 2, Line %d: %s", i, line2);
// 				if (line2[ft_strlen(line2) - 1] != '\n')
// 					printf("\n");
// 				free(line2);
// 			}
// 			if (line3)
// 			{
// 				printf("File 3, Line %d: %s", i, line3);
// 				if (line3[ft_strlen(line3) - 1] != '\n')
// 					printf("\n");
// 				free(line3);
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		perror("Put 4 arguments.\n");
// 		return (1);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
