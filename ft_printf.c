/* ************************************************************************** */
/*	*/
/*	::::::::	*/
/*   ft_printf.c	:+:	:+:	*/
/*	 +:+	*/
/*   By: rbraaksm <rbraaksm@student.codam.nl>	 +#+	 */
/*	   +#+	  */
/*   Created: 2020/01/13 20:43:19 by rbraaksm	   #+#	#+#	*/
/*   Updated: 2020/01/14 07:18:21 by rbraaksm	  ########   odam.nl	 */
/*	*/
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

typedef struct	s_flags
{
	char		type;
	int			width;
	int			prec;
	int			dot;
	int			neg;
}				t_flags;

int		putnbr(t_flags *flags, long nbr, int len)
{
	char	str[10];
	int		count;
	int		base;
	int		i;

	count = 0;
	if (nbr == 0)
		return (write(1, "0", 1));
	if (nbr == 2147483648)
		return (write(1, "2147483648", 10));
	base = 10;
	if (flags->type == 'x')
		base = 16;
	i = len - 1;
	while (nbr != 0)
	{
		if (nbr % base < 10)
			str[i] = nbr % base + '0';
		else if (flags->type == 'x')
			str[i] = nbr % base + 87;
		nbr /= base;
		i--;
	}
	write(1, str, len);
	return (len);
}

int		digit(va_list args, t_flags *flags)
{
	int		count;
	long	nbr;
	long	tmp;
	int		len;

	nbr = va_arg(args, int);
	len = 0;
	count = 0;
	if (nbr < 0)
	{
		flags->neg = 1;
		nbr *= -1;
	}
	tmp = nbr;
	while (tmp > 0)
	{
		tmp = tmp / (flags->type == 'd' ? 10 : 16);
		len++;
	}
	if (nbr == 0)
		len = 1;
	flags->width = flags->width - flags->neg - (len > flags->prec ? len : flags->prec);
	while (flags->width > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->neg == 1)
		count += write(1, "-", 1);
	if (flags->prec > len)
	{
		while (flags->prec > len)
		{
			count += write(1, "0", 1);
			flags->prec--;
		}
	}
	if (nbr == 0 && flags->prec == 0)
		return (count);
	count += putnbr(flags, nbr, len);
	return (count);
}

int		string(va_list args, t_flags *flags)
{
	int		count;
	int		len;
	int		i;
	char	*str;

	str = va_arg(args, char*);
	count = 0;
	len = 0;
	i = 0;
	while (str[len] != '\0')
		len++;
	flags->width = flags->width - (flags->dot == 0 ? len : flags->prec);
	while (flags->width > 0)
	{
		count += write(1, " ", 1);
		flags->width--;
	}
	if (flags->dot == 0)
		count += write(1, str, len);
	else
	{
		while (flags->prec > 0)
		{
			count += write(1, &str[i], 1);
			flags->prec--;
			i++;
		}
	}
	return (count);
}

void	width_prec(const char *str, t_flags *flags)
{
	int		dot;
	int		i;
	int		w;
	int		p;

	dot = 0;
	w = 0;
	while (str[i] != flags->type)
	{
		if ((str[i] >= '0' && str[i] <= '9') && flags->dot == 0)
		{
			flags->width += str[i] - '0';
			if (str[i + 1] >= '0' && str[i + 1] <= '9')
				flags->width *= 10;
		}
		else if (str[i] == '.')
			flags->dot = 1;
		else if ((str[i] >= '0' && str[i] <= '9') && flags->dot == 1)
		{
			flags->prec += str[i] - '0';
			if (str[i + 1] >= '0' && str[i + 1] <= '9')
				flags->prec *= 10;
		}
		i++;
	}
}

int		ft_flags(va_list args, t_flags *flags, const char *str, int *index)
{
	int		count;
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'd')
			flags->type = 'd';
		else if (str[i] == 's')
			flags->type = 's';
		else if (str[i] == 'x')
			flags->type = 'x';
		if (flags->type != ' ')
			break ;
		i++;
	}
	*index += i;
	width_prec(str, flags);
	if (flags->type == 's')
		count = string(args, flags);
	else if (flags->type == 'd' || flags->type == 'x')
		count = digit(args, flags);
	return (count);
}

void	empty_flags(t_flags *flags)
{
	flags->type = ' ';
	flags->width = 0;
	flags->prec = 0;
	flags->dot = 0;
	flags->neg = 0;
}

int		ft_printf(const char *str, ...)
{
	va_list args;
	t_flags	flags;
	int		count;
	int		index;

	va_start(args, str);
	count = 0;
	index = 0;
	while (str[index] != '\0')
	{
		empty_flags(&flags);
		if (str[index] == '%')
			count += ft_flags(args, &flags, &(str[index]), &index);
		else if (str[index] != '%')
			count += write(1, &str[index], 1);
		index++;
	}
	va_end(args);
	return (count);
}

int		main(void)
{
	int		str;
	int		res;
	int		res2;

	str = 454546;
	res = ft_printf("%s is %d jaar %d", "Joep", 5, 4);
	printf("\n");
	res2 = printf("%s is %d jaar %s", "Joep", 5, "oud");
	// printf("\n");
	// printf("Mine = %d\n", res);
	// printf("Real = %d\n", res2);
	return (0);
}
