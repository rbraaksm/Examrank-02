/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbraaksm <rbraaksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 11:45:15 by rbraaksm       #+#    #+#                */
/*   Updated: 2020/01/20 15:28:29 by rbraaksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

typedef struct	s_data
{
	char		type;
	int			prec;
	int			width;
	int			dot;
	int			neg;
	int			index;
	int			count;
}				t_data;

void	find_width_prec(t_data *flags, const char *str)
{
	while ((str[flags->index] >= '0' && str[flags->index] <= '9') && flags->dot == 0)
	{
		flags->width += str[flags->index] - '0';
		flags->index++;
		if (str[flags->index] >= '0' && str[flags->index] <= '9')
			flags->width *= 10;
	}
	if (str[flags->index] == '.')
	{
		flags->dot = 1;
		flags->index++;
	}
	while ((str[flags->index] >= '0' && str[flags->index] <= '9') && flags->dot == 1)
	{
		flags->prec += str[flags->index] - '0';
		flags->index++;
		if (str[flags->index] >= '0' && str[flags->index] <= '9')
			flags->prec *= 10;
	}
	if (str[flags->index] == 's')
		flags->type = 's';
	if (str[flags->index] == 'd')
		flags->type = 'd';
	if (str[flags->index] == 'x')
		flags->type = 'x';
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	string(va_list args, t_data *flags)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = va_arg(args, char *);
	if (str == NULL && flags->dot == 1 && flags->prec == 0 && flags->width == 0)
		return ;
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	flags->width = flags->width - (len > flags->prec ? flags->prec : len);
	while (flags->width > 0)
	{
		flags->count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->dot == 0)
	{
		while (str[i] != '\0')
		{
			flags->count += write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		flags->prec = (len < flags->prec ? len : flags->prec);
		while (flags->prec > 0)
		{
			flags->count += write(1, &str[i], 1);
			i++;
			flags->prec--;
		}
	}
}

int		length(t_data *flags, long nbr)
{
	int		len;

	len = 0;
	while (nbr > 0)
	{
		len++;
		nbr /= flags->type == 'd' ? 10 : 16;
	}
	return (len);
}

void	putnbr(t_data *flags, long nbr, int len)
{
	char	str[16];
	int		i;
	int		base;

	i = len - 1;
	base = 10;
	if (nbr == 0)
	{
		flags->count += write(1, "0", 1);
		return ;
	}
	if (flags->type == 'x')
		base = 16;
	while (nbr != 0)
	{
		if (nbr % base < 10)
			str[i] = (nbr % base) + '0';
		else if (flags->type == 'x')
			str[i] = (nbr % base) + 87;
		nbr /= base;
		i--;
	}
	flags->count += write(1, str, len);
}

void	number(va_list args, t_data *flags)
{
	long	nbr;
	int		len;

	nbr = va_arg(args, int);
	len = 0;
	if (nbr == -2147483648)
	{
		flags->neg = 1;
		nbr = 2147483648;
	}
	if (nbr < 0)
	{
		flags->neg = 1;
		nbr = nbr * -1;
	}
	if (nbr == 0)
		len = 1;
	else
		len = length(flags, nbr);
	flags->width = flags->width - flags->neg - (len > flags->prec ? len : flags->prec);
	while (flags->width > 0)
	{
		flags->count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->neg == 1)
		flags->count += write(1, "-", 1);
	while ((flags->prec - len) > 0)
	{
		flags->count += write(1, "0", 1);
		flags->prec--;
	}
	if (nbr == 0 && flags->dot == 1 && flags->prec == 0)
		return ;
	putnbr(flags, nbr, len);
}

void	ft_start(va_list args, t_data *flags, const char *str)
{
	find_width_prec(flags, str);
	// printf("[WIDTH]  %d\n", flags->width);
	// printf("[PREC]   %d\n", flags->prec);
	// printf("[DOT]    %d\n", flags->dot);
	if (flags->type == 's')
		string(args, flags);
	else
		number(args, flags);
}

void	empty_flags(t_data *flags)
{
	flags->width = 0;
	flags->prec = 0;
	flags->dot = 0;
	flags->neg = 0;
	flags->type = ' ';
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	t_data	flags;

	flags.index = 0;
	flags.count = 0;
	va_start(args, str);
	while (str[flags.index] != '\0')
	{
		empty_flags(&flags);
		if (str[flags.index] == '%')
		{
			flags.index++;
			ft_start(args, &flags, str);
		}
		else
			flags.count += write(1, &str[flags.index], 1);
		flags.index++;
	}
	va_end(args);
	return (flags.count);
}

