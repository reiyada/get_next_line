/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:46 by ryada             #+#    #+#             */
/*   Updated: 2024/11/25 22:29:32 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

    i = 0;
    if (!str)
    {
        return (0);
    }
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *ptr, size_t num)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)ptr;
	while (num > 0)
	{
		*byte_ptr = 0;
		byte_ptr++;
		num--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *)malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, (nmemb * size));
	return (array);
}

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    i = 0;
    if (!src)
        return (0);
    if (dstsize > 0)
    {
        while (src[i] && i < dstsize - 1)
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (ft_strlen(src));
}



char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    size_t len1;
    size_t len2;
    size_t i;
    size_t j;
    
    len1= 0;
    len2 = 0;
    if (s1)
        len1 = ft_strlen(s1);
    if (s2)
        len2 = ft_strlen(s2);
    result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return (NULL);
    i = 0;
    if (s1)
    {
        while (i < len1)
        {
            result[i] = s1[i];
            i++;
        }
    }
    j = 0;
    if (s2)
    {
        while (j < len2)
        {
            result[i] = s2[j];
            i++;
            j++;
        }
    }
    result[i] = '\0';
    return (result);
}


int ft_find_line_end(char *str)
{
    int i;

    if (!str)
        return (-1);
    i = 0;
    while (str[i])
    {
        if(str[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char *ft_extract_current_line(char *str)
{
    char *current_line;
    int end;

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


char *ft_join_and_free(char *text, char *buffer)
{
    char *temp;

    temp = ft_strjoin(text, buffer);
    if (!temp)
    {
        free(text);
        return (NULL);
    }
    free(text);
    return (temp);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	target;
	int				i;

	target = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == target)
			return ((char *)&s[i]);
		i++;
	}
	if (target == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
char *ft_read_update_remainder(int fd, char *remainder)
{
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;

    if (!remainder)
    {
        remainder = ft_calloc(1, 1);
        if (!remainder)
            return (NULL); // Handle allocation failure
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        remainder = ft_join_and_free(remainder, buffer);
        if (!remainder)
            return (NULL); // Handle malloc failure
        if (ft_strchr(remainder, '\n'))
            break; // Stop reading once a newline is found
    }

    if (bytes_read == 0 && remainder && *remainder == '\0') // Handle empty remainder
    {
        free(remainder);
        return (NULL);
    }

    if (bytes_read == -1) // Handle read errors
    {
        free(remainder);
        return (NULL);
    }

    return (remainder);
}

char *ft_update_data(char *remainder)
{
    char *new_remainder;
    int end;

    if (!remainder)
        return (NULL);

    end = ft_find_line_end(remainder);
    if (end == -1 || remainder[end + 1] == '\0') // No remaining data
    {
        free(remainder);
        return (NULL);
    }

    new_remainder = ft_calloc(1, ft_strlen(remainder) - end);
    if (!new_remainder)
    {
        free(remainder);
        return (NULL); // Handle allocation failure
    }

    ft_strlcpy(new_remainder, &remainder[end + 1], ft_strlen(&remainder[end + 1]) + 1);
    free(remainder);

    if (!*new_remainder) // Free empty new_remainder
    {
        free(new_remainder);
        return (NULL);
    }

    return (new_remainder);
}


// char *ft_read_update_remainder(int fd, char *remainder)
// {
//     char buffer[BUFFER_SIZE + 1];
//     int bytes_read;

//     if (!remainder)
//         return (NULL);
//     while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
//     {
//         buffer[bytes_read] = '\0';
//         remainder = ft_join_and_free(remainder, buffer);
//         if (ft_strchr(remainder, '\n'))
//         {
//             free (remainder);
//             return (NULL);
//         }
//     }
//     if (bytes_read == 0 && remainder && *remainder == '\0')
//     {
//         free (remainder);
//         return (NULL);
//     }
//     if (bytes_read == -1)
//     {
//         free(remainder);
//         return (NULL);
//     }
//     return(remainder);
// }

// char *ft_update_data(char *remainder)
// {
//     char *new_remainder;
//     int end;
    
//     if (!remainder)
//         return (NULL);
//     end = ft_find_line_end(remainder);
//     if (end == -1 || remainder[end + 1] == '\0')
//     {
//         free(remainder);
//         return (NULL);
//     }
//     new_remainder = ft_calloc(1, ft_strlen(remainder) - end);
//     if (!new_remainder || !*new_remainder)
//     {
//         free (remainder);
//         free (new_remainder);
//         return (NULL);
//     }
//     ft_strlcpy(new_remainder, &remainder[end + 1], ft_strlen(&remainder[end + 1]) + 1);
//     free(remainder);
//     return (new_remainder);
// }