/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rei <rei@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:39 by ryada             #+#    #+#             */
/*   Updated: 2024/11/27 19:52:55 by rei              ###   ########.fr       */
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

int		ft_read_into_buffer(int fd, char *buffer);

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	*ft_read_and_update_remainder(int fd, char *remainder, char *buffer);
char	*ft_extract_line_from_remainder(char **remainder);
char	*ft_finalize_line(char **remainder, char *buffer);

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);

#endif