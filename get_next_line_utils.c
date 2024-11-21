/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryada <ryada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:46 by ryada             #+#    #+#             */
/*   Updated: 2024/11/21 17:14:36 by ryada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*result;
// 	size_t	len;
// 	size_t	i;
// 	size_t	j;

// 	len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	result = (char *)malloc(len * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		result[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != '\0')
// 	{
// 		result[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	result[i] = '\0';
// 	return (result);
// }

// int ft_find_new_line(char *str)
// {
//     int i;

//     if (!str)
//         return (-1);
//     i = 0;
//     while (str[i])
//     {
//         if(str[i] == '\n')
//             return i;
//         i++;
//     }
//     return (-1);
// }

char *ft_extract_current_line(char *str, int i)
{
    char *current_line;
    int start;
    int end;
    int j;

    if (!str || str[0] == '\0')
        return (NULL);
    end = i;
    while(i > 0)
    {
        if (str[i - 1] != '\n')
            i--;
        else
            break;
    }
    start = i;
    current_line = (char *)malloc(sizeof(char) * (end - start + 2)); // '\n' + '\0'
    if (!current_line)
        return (NULL);
    j = 0;
    while (str[i] != '\n' && str[i] != '\0')
    {
        current_line[j] = str[i];
        j++;
        i++;
    }
    if (str[i] == '\n')
        current_line[j] = '\n';
    current_line[j] = '\0';
    return (current_line);
}

int main(void)
{
    char str[] = "A\nBB\nCCC";
    int i = 16;
    char *result = ft_extract_current_line(str, i);
    printf ("%s", result);
    free (result);
    return (0);
}