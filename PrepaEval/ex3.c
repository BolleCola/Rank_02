#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

static void ft_putstr(char *str, int *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	*c += i;
}

static void ft_putnbr(long nbr, int *c)
{
	int w;

	w = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
		*c+=1;
	}
	if (nbr <= 9)
	{
		w = nbr + '0';
		write(1, &w, 1);
		*c+=1;
	}
	else
	{
		ft_putnbr(nbr / 10, &*c);
		w = (nbr % 10) + '0';
		write(1, &w, 1);
		*c+=1;
	}
}

static void ft_hexa(unsigned int nbr, int *c)
{
	unsigned int temp;

	temp = nbr % 16;
	if (temp <= 9)
		temp = temp + 48;
	else if (temp >= 10)
		temp = temp + 87;
	if ((nbr / 16) != 0)
		ft_hexa((nbr / 16), &*c);
	write(1, &temp, 1);
	*c+=1;
}

static void	letter(char let, va_list arg, int *c)
{
	if (let == 's')
		ft_putstr(va_arg(arg, char *), &*c);
	else if (let == 'd')
		ft_putnbr(va_arg(arg, long), &*c);
	else if (let == 'x')
		ft_hexa(va_arg(arg, unsigned int), &*c);
}

int ft_printf(const char *str, ...)
{
	va_list arg;
	int		i;
	int		c;

	va_start(arg, str);
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			letter(str[i + 1], arg, &c);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			c++;
		}
		i++;
	}
	va_end(arg);
	return (c);
}

int main ()
{
	int	x;
	int	y;

	ft_printf("--- test avec s ---\n");
	printf("printf : %s\n", "les chausettes de la duchesse sont elle seche ou archi-seche//test apres string");
	ft_printf("ft_printf : %s\n", "les chausettes de la duchesse sont elle seche ou archi-seche//test apres string");

	ft_printf("--- test avec d ---\n");
	printf("printf : %d\n", 123456789);
	ft_printf("ft_printf : %d\n", 123456789);

	ft_printf("--- test avec x min ---\n");
	printf("printf : %x\n", -4545);
	ft_printf("ft_printf : %x\n", -4545);

	ft_printf("--- test le retour de int ---\n");
	x = printf("je test %s %x %d\n", "test", 123, 123);
	printf("%d\n", x);
	y = ft_printf("je test %s %x %d\n", "test", 123, 123);
	printf("%d\n", y);
}
