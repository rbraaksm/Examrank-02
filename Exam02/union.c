#include <unistd.h>

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		check(char *str, int i, char c)
{
	while (i > 0)
	{
		i--;
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	ft_union(char **argv)
{
	int		i;

	i = 1;
	write(1, &argv[1][0], 1);
	while (argv[1][i] != '\0')
	{
		if (check(argv[1], i, argv[1][i]) == 0)
			write(1, &argv[1][i], 1);
		i++;
	}
	i = 0;
	while (argv[2][i] != '\0')
	{
		if (check(argv[1], ft_strlen(argv[1]), argv[2][i]) == 0 && check(argv[2], i, argv[2][i]) == 0)
			write(1, &argv[2][i], 1);
		i++;
	}
}

int		main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv);
	write(1, "\n", 1);
	return (1);
}