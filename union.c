/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   union.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 10:38:21 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/13 12:42:36 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		length(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

int		check(char *str, int i, char c)
{
	while (i >= 0)
	{
		i--;
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	ft_union(char **argv)
{
	char	*str1;
	char	*str2;
	int		i1;
	int		i2;

	str1 = argv[1];
	str2 = argv[2];
	i1 = 0;
	while (str1[i1] != '\0')
	{
		if (check(str1, i1, str1[i1]) == 0)
		{
			write(1, &str1[i1], 1);
			i1++;
		}
		else
			i1++;
	}
	i1 = length(str1);
	i2 = 0;
	while (str2[i2] != '\0')
	{
		if (check(str1, i1, str2[i2]) == 0 && check(str2, i2, str2[i2]) == 0)
		{
			write(1, &str2[i2], 1);
			i2++;
		}
		else
			i2++;
	}
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		write(1, "\n", 1);
	else
		ft_union(argv);
	return (0);
}
