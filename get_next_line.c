/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:26:50 by ryada             #+#    #+#             */
/*   Updated: 2024/11/28 10:35:22 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_update_remainder(int fd, char *remainder, char *buffer)
{
	int		bytes_read;
	char	*temp;//to store the new remiander so we can free the old one

	temp = NULL;
	bytes_read = 1;//to enter the loop at first
	while (bytes_read > 0)//as long as we can read
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)//read fails or read finished
			break ;
		buffer[bytes_read] = '\0';//set '\0' at the end
		temp = ft_strjoin(remainder, buffer);//add the string we just read to the old remainder
		if (!temp)//allocation fail
			return (free(remainder), NULL);
		free(remainder);//free the old one
		remainder = temp;//restore the new one
		if (ft_strchr(remainder, '\n'))//if remainder contains '\n'
			break ;
	}
	if (bytes_read < 0)//read fails
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);//return the new remainder
}

char	*ft_extract_line_from_remainder(char **remainder)//so we can set remainder even as NULL or free it
{
	char	*line;
	char	*newline_ptr;
	char	*temp;
	size_t	line_length;

	newline_ptr = ft_strchr(*remainder, '\n');//find the new line pointer
	if (!newline_ptr)//search fails or error bc it must contains '\n'
		return (NULL);
	line_length = newline_ptr - *remainder + 1;//remove the len of str after '\n from the original remainder len and add '\n'
	line = (char *)malloc(sizeof(char) * (line_length + 1));//+1 to add '\0'
	if (!line)//allocation fails
		return (NULL);
	ft_strlcpy(line, *remainder, line_length + 1);//+1 to add '\0' at the end
	temp = ft_strdup(newline_ptr + 1);//store the string after '\n'
	if (!temp)//allocation fails
		return (free(line), NULL);
	free(*remainder);//free the old(long) one
	*remainder = temp;//restore the new one (after'\n')
	if ((*remainder)[0] == '\0')//if there is no remainder string which should not happen
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (line);//return the line until '\n' added '\0' in the end
}

char	*ft_finalize_line(char **remainder, char *buffer)
{
	char	*line;

	if (*remainder && **remainder)//if the memory has been allocated and remainer is not empty
	{
		line = ft_strdup(*remainder);//final line
		if (!line)// allocation fail
		{
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		line = NULL;// the end line
	free(*remainder);
	*remainder = NULL;
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0) //if it fails to open, or there is not enough memory space foe buffer
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1); //+1 is for '\0' bc read does not add it
	if (!buffer)
		return (NULL); // allocation fail
	if (!remainder)//if there is nothing in remainder
	{
		remainder = ft_strdup("");//set it empty
		if (!remainder)//allocation fails
			return (free(buffer), NULL);//free buffer and return NULL
	}
	remainder = ft_read_and_update_remainder(fd, remainder, buffer);//readuntil remainder contains '\n' or we finish reading, then update it
	if (!remainder)//read or update fails
		return (free(buffer), NULL);
	line = ft_extract_line_from_remainder(&remainder);// the line until '\n' added '\0' in the end
	if (line)//if it fails
		return (free(buffer), line);
	return (ft_finalize_line(&remainder, buffer));
}

int main(int argc, char **argv)
{
	char *line;
	int fd;
	int i;

	i = 1;
	if (argc > 1)
	{
		fd = open(argv[1],O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening file\n");
			return (1);
		}
		line = get_next_line(fd);
		while (line)
		{
			printf("LINE %d:%s", i, line);
			free(line);
			i++;
			line = get_next_line(fd);
		}
		close(fd);
	}
	else
		perror("Incorrect argument amount\n");
	return (0);
}
