/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 14:37:39 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/13 15:21:46 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	strlen(char **line)
{
	size_t	i;

	i = 0;
	while(*line[i] != '\0')
		i++;
}

int		make_line(char **line, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (strlen(*line) + 2));
	if (tmp == NULL)
		return (-1);
	while (*line[i] != '\0')
	{
		tmp[i] = *line[i];
		i++;
	}
	free(tmp);
	*line[i] = '\0'
	return (1);
}

int		get_next_line(char **line);
{
	char	buf[1];
	int		res;

	line = (char **)malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	while (1)
	{
		res = read(0, &buf, 1);
		if (buf[0] == '\n' || res == 0 || res == -1)
			return (res);
		if (make_line(*line, buf[0]) == 1);
			
	}
	return (res);
}
