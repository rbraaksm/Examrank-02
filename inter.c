/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 12:00:09 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/13 14:12:52 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		length(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int		check(char *str, int i, char c)
{
	while (i >= 0)
	{
		i--;
		if (str[i] == c)
			return (0);
	}
	return (1);
}

void	inter(char **argv)
{
	int		i;
	int		len;

	i = 0;
	len = length(argv[2]);
	if (check(argv[2], len, argv[1][i]) == 0)
	{
		write(1, &argv[1][i], 1);
		i++;
	}
	while (argv[1][i] != '\0')
	{
		if (check(argv[1], i, argv[1][i]) == 1)
		{
			if (check(argv[2], len, argv[1][i]) == 0)
				write(1, &argv[1][i], 1);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		inter(argv);
	write(1, "\n", 1);
	return (0);
}
