/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:46 by ryada             #+#    #+#             */
/*   Updated: 2024/11/25 15:37:49 by ryada            ###   ########.fr       */
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

char *ft_update_data(char *remainder)
{
    char *new_remainder;
    int end;
    int i;
    
    if (!remainder)
        return (NULL);
    end = ft_find_line_end(remainder);
    if (end == -1 || remainder[end + 1] == '\0')
    {
        free(remainder);
        return (NULL);
    }
    new_remainder = (char *)malloc(sizeof(char) * (ft_strlen(remainder) - end));
    if (!new_remainder)
    {
        free (remainder);
        return (NULL);
    }
    i = 0;
    end++;
    while (remainder[end])
        new_remainder[i++] = remainder[end++];
    new_remainder[i] = '\0';
    free(remainder);
    // printf("New remainder after update: '%s'\n", new_remainder);
    return (new_remainder);
}

// void ft_free_remained_data(char **data)
// {
//     if (*data) {
//         free(*data);
//         *data = NULL;
//     }
// }


// int main(void)
// {
//     char str[] = "HELLO\nKONNICHIWA\nBONJOUR";
//     int i = 5;
//     char *result = ft_update_data(str, i);
//     printf ("%s\n", result);
//     free (result);
//     return (0);
// }