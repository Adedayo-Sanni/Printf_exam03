#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

# define HEX_LOW "0123456789abcdef"

int ft_putchar(char c)
{
  write (1, &c, 1);
}

int	ft_puthex_lower(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 15)
		i += ft_puthex_lower(n / 16);
	i += write(1, &HEX_LOW[n % 16], 1);
	return (i);
}
int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		i += write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			i += ft_putchar('-');
			n *= -1;
		}
		if (n < 10)
		{
			i += ft_putchar(n + 48);
		}
		else
		{
			i += ft_putnbr(n / 10);
			i += ft_putnbr(n % 10);
		}
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count_len;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	count_len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' &&  ((format[i + 1] == 's') || (format[i + 1] == 'd') || (format[i + 1] == 'x')))
		{
			i++;
     if (format[i] == 's')
      count_len += ft_putstr(va_arg(args, char *));
    else if (format[i] == 'd')
      count_len += ft_putnbr(va_arg(args, int));
    else if (format[i] == 'x')
      count_len += ft_puthex_lower(va_arg(args, unsigned int));
		}
		else
			count_len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count_len);
}