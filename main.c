#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif


int		ft_printf(const char *str, ...);

int		main(void)
{
	char	*str;
	int		nbr;
	int		res;
	int		res1;

	str = NULL;
	nbr = 7077;
	res = ft_printf("[Mine] %40.20s", str);
	printf("\n");
	res1 = printf("[Real] %40.20s", str);
	printf("\n");
	printf("[Mine res] %d\n", res - 7);
	printf("[Real res] %d\n", res1 -7 );
	return (1);
}

