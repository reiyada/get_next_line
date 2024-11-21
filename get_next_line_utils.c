/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:46 by ryada             #+#    #+#             */
/*   Updated: 2024/11/22 00:36:17 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
        while (i < len1)
        {
            result[i] = s1[i];
            i++;
        }
    j = 0;
    if (s2)
        while (j < len2)
            result[i++] = s2[j++];
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
        if(str[i] == '\n' || str[i] == '\0')
            return i;
        i++;
    }
    return (-1);
}

char *ft_extract_current_line(char *str, int line_end)
{
    char *current_line;
    int i;
    
    current_line = (char *)malloc(sizeof(char) * (line_end + 2));
    if (!current_line)
        return (NULL);
    i = 0;
    while (i <= line_end)
    {
        current_line[i] = str[i];
        i++;
    }
    current_line[i] = '\0';
    return (current_line);
}

char *ft_update_data(char *remained_data, int line_end)
{
    int i;
    char *new_data;

    if (!remained_data || !remained_data[line_end + 1])
    {
        free(remained_data);
        return (NULL);
    }
    new_data = (char *)malloc(ft_strlen(remained_data + line_end + 1) + 1);
    if (!new_data)
        return (NULL);
    line_end++;
    i = 0;
    while (remained_data[line_end])
        new_data[i++] = remained_data[line_end++];
    new_data[i] = '\0';
    free(remained_data);
    return (new_data);
}

void ft_free_remained_data(char **data)
{
    if (*data) {
        free(*data);
        *data = NULL;
    }
}


// int main(void)
// {
//     char str[] = "HELLO\nKONNICHIWA\nBONJOUR";
//     int i = 5;
//     char *result = ft_update_data(str, i);
//     printf ("%s\n", result);
//     free (result);
//     return (0);
// }