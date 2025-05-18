/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:59:00 by nqasem           #+#    #+#             */
/*   Updated: 2024/10/07 20:29:52 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_nextline(char *buf, char *l)
{
	size_t	i;
	size_t	j;
	char	*rem;

	i = ft_strlen(l);
	j = 0;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	while (buf[i++])
		j++;
	rem = malloc((j + 1));
	i = ft_strlen(l);
	j = 0;
	while (buf[i + j])
	{
		rem[j] = buf[i + j];
		j++;
	}
	rem[j] = '\0';
	free(buf);
	return (rem);
}

char	*ft_line(char *res)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!res)
		return (NULL);
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (res[i] && res[i] != '\n')
	{
		line[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *buf)
{
	char	*temp;
	ssize_t	bytread;

	bytread = 1;
	while (bytread > 0 && !ft_strchr(buf))
	{
		temp = malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (NULL);
		bytread = read(fd, temp, BUFFER_SIZE);
		if (bytread == -1 || (!buf && bytread == 0))
		{
			free(temp);
			return (NULL);
		}
		temp[bytread] = '\0';
		buf = ft_strjoin(buf, temp);
		free(temp);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	tmp = ft_read(fd, buf[fd]);
	if (!tmp)
	{
		if (buf[fd])
			free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	buf[fd] = tmp;
	line = ft_line(buf[fd]);
	buf[fd] = ft_nextline(buf[fd], line);
	return (line);
}

/*
int	main(int argc, char *argv[])
{
	int	i = 0;
	int	fd[argc];
	fd[i] = 1;
	while(fd[i] > 0)
	{
		fd[i] = open(argv[i+1], O_RDONLY);
		char *line;
		//printf("---------------->{%d}\n", fd[i]);
		while ((line = get_next_line(fd[i])) != NULL)
		{
			printf("%s", line);
			free(line);
		}

 
		close(fd[i]);
		if (fd[i] < 0)
		{
			return (0);
		}
		i++;
	}
	
	return (0);
}*/
