/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhamdan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 04:23:39 by nqasem           #+#    #+#             */
/*   Updated: 2024/09/14 04:33:58 by nqasem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(const char *str);
char	*ft_strchr(char *s);
char	*get_next_line(int fd);
void	*ft_calloc(size_t n, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
