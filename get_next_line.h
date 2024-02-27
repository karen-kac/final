/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:01 by myokono           #+#    #+#             */
/*   Updated: 2024/02/27 21:35:03 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

int		append_read_data(int fd, char **stored, char *buffer);

char	*get_next_line(int fd);

char	*extract_line(char **stored);

int		update_stored(char **stored);

int		read_and_store(int fd, char **stored);

char	*ft_strjoin(char *s1, char const *s2);

char	*ft_strchr(const char *s, int c);

size_t	ft_strlen(const char *str);

void	free_and_null(char **ptr);

#endif