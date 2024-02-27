/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:34:48 by myokono           #+#    #+#             */
/*   Updated: 2024/02/27 22:41:13 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char **stored)
{
	char	*line;
	int		copy_len;
	int		i;

	if (ft_strchr(*stored, '\n') == NULL)
		copy_len = ft_strlen(*stored);
	else
		copy_len = ft_strchr(*stored, '\n') - *stored + 1;
	line = malloc(copy_len + 1);
	if (!line)
	{
		free_and_null(stored);
		return (NULL);
	}
	i = 0;
	while (i < copy_len)
	{
		line[i] = (*stored)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	update_stored(char **stored)
{
	char	*new_stored;
	int		i;
	int		j;
	int		cut_len;

	if (ft_strchr(*stored, '\n') == NULL)
		return (0);
	cut_len = ft_strchr(*stored, '\n') - *stored + 1;
	new_stored = malloc(ft_strlen(*stored) - cut_len + 1);
	if (!new_stored)
		return (-1);
	i = 0;
	j = cut_len;
	while ((*stored)[j])
		new_stored[i++] = (*stored)[j++];
	new_stored[i] = '\0';
	free_and_null(stored);
	*stored = new_stored;
	return (1);
}

static int	append_read_data(int fd, char **stored, char *buffer)
{
	char	*temp;
	ssize_t	read_len;

	read_len = 1;
	while (!ft_strchr(*stored, '\n') && read_len != 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
			return (-1);
		if (read_len == 0)
			return (0);
		buffer[read_len] = '\0';
		temp = *stored;
		*stored = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (1);
}

static int	read_and_store(int fd, char **stored)
{
	char	*buffer;
	int		flag;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	flag = append_read_data(fd, stored, buffer);
	free(buffer);
	return (flag);
}

char	*get_next_line(int fd)
{
	static char	*stored[OPEN_MAX + 1];
	char		*line;
	int			flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || OPEN_MAX < fd)
		return (NULL);
	flag = read_and_store(fd, &stored[fd]);
	if (flag == -1 || (flag == 0 && (!stored[fd] || *stored[fd] == '\0')))
	{
		free_and_null(&stored[fd]);
		return (NULL);
	}
	line = extract_line(&stored[fd]);
	flag = update_stored(&stored[fd]);
	if (flag == -1 || flag == 0)
		free_and_null(&stored[fd]);
	if (flag == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
