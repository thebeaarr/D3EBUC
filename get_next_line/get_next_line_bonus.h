/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:44:25 by mlakhdar          #+#    #+#             */
/*   Updated: 2024/11/30 18:44:26 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define FDS_MAX 1024

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
char	*get_line(char *buffer, int i);
char	*trim_the_buffer(char *buffer, int i);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	merging(const char *s, int mode);
#endif
