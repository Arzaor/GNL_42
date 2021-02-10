/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:56:43 by jbarette          #+#    #+#             */
/*   Updated: 2021/02/10 10:38:40 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_all(char *save)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	if (!(rest = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1))))
		return (0);
	i++;
	while (save[i])
		rest[j++] = save[i++];
	rest[j] = '\0';
	free(save);
	return (rest);
}

char	*ft_puts_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\0')
		i++;
	if (!(line = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int		get_next_line(int fd, char **line)
{
	static char *save[4096];
	char		*buff;
	int			open;

	open = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!has_return(save[fd]) && open != 0)
	{
		if ((open = read(fd, buff, BUFFER_SIZE)) == -1)
		{
			free(buff);
			return (-1);
		}
		buff[open] = '\0';
		save[fd] = ft_strjoin(save[fd], buff);
	}
	free(buff);
	*line = ft_puts_line(save[fd]);
	save[fd] = save_all(save[fd]);
	if (open == 0)
		return (0);
	return (1);
}
