/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 08:15:58 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/20 11:33:22 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 4

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	char	*new;
	char	tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	new = malloc(sizeof(char *) * (len + 1));
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*newstr;
	int			index;
	int			index2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	index = 0;
	index2 = 0;
	newstr = malloc(sizeof(char *) * (ft_strlen(s1) + (ft_strlen(s2) + 1)));
	if (!newstr)
		return (NULL);
	while (s1[index] != '\0')
	{
		newstr[index] = s1[index];
		index++;
	}
	while (s2[index2] != '\0')
	{
		newstr[index + index2] = s2[index2];
		index2++;
	}
	newstr[index + index2] = '\0';
	return (newstr);
}

char	*ft_substr(char *str, int start, int len)
{
	int		i;
	int		n;
	char	*new;

	i = 0;
	n = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	if (!*str || start >= i)
		return (ft_strdup(""));
	if ((i - start) < len)
		new = malloc(sizeof(char *) * ((i - start) + 1));
	else
		new = malloc(sizeof(char *) * (len + 1));
	while (n < len)
	{
		new[n] = str[start + n];
		n++;
	}
	new[n] = '\0';
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char*)&(s[i]));
		i++;
	}
	if (s[i] == '\0' && s[i] == (unsigned char)c)
		return ((char*)&(s[i]));
	return (NULL);
}

char	*make_string(char *str, int *ret)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		i;

	i = 0;
	while (*ret > 0)
	{
		*ret = read(0, buf, BUFFER_SIZE);
		if (*ret < 0)
		{
			free(str);
			return (0);
		}
		buf[*ret] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if (str == NULL)
			return (0);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

char	*make_line(char **line, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] == '\0' || str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		*line = ft_substr(str, 0, i);
		if (*line == NULL)
		{
			free(str);
			return (0);
		}
		tmp = str;
		str = ft_strdup(&(str[i + 1]));
		free(tmp);
		if (str == NULL)
		{
			free(str);
			return (0);
		}
	}
	return (str);
}

int		last_line(char **line, char *str)
{
	*line = ft_strdup(str);
	free(str);
	if (*line == NULL)
		return (-1);
	return (0);
}

int		get_next_line(char **line)
{
	static char	*str;
	int			ret;

	ret = 1;
	if (!str)
		str = ft_strdup("");
	while (ret > 0)
	{
		if ((ft_strchr(str, '\n')) != NULL)
		{
			str = make_line(line, str);
			if (str == NULL)
				return (-1);
			return (1);
		}
		str = make_string(str, &ret);
		if (str == NULL)
			return (-1);
	}
	return (last_line(line, str));
}

int		main(void)
{
	char	*str;
	int		res;

	res = 1;
	while (res > 0)
	{
		res = get_next_line(&str);
		printf("[Result] %d   [String]  %s\n", res, str);
		free(str);
	}
	return (1);
}
