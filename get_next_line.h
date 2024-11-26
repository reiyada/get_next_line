/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:39 by ryada             #+#    #+#             */
/*   Updated: 2024/11/26 12:06:03 by rei              ###   ########.fr       */
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

void	ft_bzero(void *ptr, size_t num);

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_extract_current_line(char *str);
char	*ft_update_data(char *str);
char	*ft_join_and_free(char *text, char *buffer);
char	*ft_read_update_remainder(int fd, char *remainder);
char	*ft_strchr(const char *s, int c);

int		ft_find_line_end(char *str);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif