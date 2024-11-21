/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:39 by ryada             #+#    #+#             */
/*   Updated: 2024/11/22 00:14:39 by rei              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

char    *get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char    *ft_extract_current_line(char *str, int i);
char    *ft_update_data(char *remained_data, int line_end);


int     ft_find_line_end(char *str);

size_t	ft_strlen(const char *str);

void ft_free_remained_data(char **data);

#endif