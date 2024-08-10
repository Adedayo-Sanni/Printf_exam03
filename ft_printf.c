#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

int ft_putchar(char c)
{
 return (write(1, &c, 1)) ;
}

int ft_putstr(char *str)
{
  int i;

  i = 0;
  if (!str)
    return(ft_putstr("(null)"));
  while (str[i] != '\0')
  {
    ft_putchar(str[i]);
    i++;
  }
  return(i);
}

int ft_putnbr(int nbr)
{
    int i = 0;

    if (nbr == INT_MIN)
        return ((ft_putstr("-2147483648")));
    if (nbr < 0)
    {
        i += ft_putchar('-');
        nbr *= -1;
    }
    if (nbr < 10)
        i += ft_putchar(nbr + 48);
    else
    {
        i += ft_putnbr(nbr / 10);
        i += ft_putnbr(nbr % 10);
    }
    return i;
}
int ft_puthex(unsigned int nbr)
{
  char *hex = "0123456789abcdef";
  int i = 0;

  if (nbr > 15)
    i+= ft_puthex(nbr / 16);
  i+= ft_putchar(hex[nbr % 16]);
  return (i);
}

int	ft_printf(const char *format, ...)
{
  va_list args;
  int count_len = 0;
  int i = 0;
  if (format == NULL)
    return (-1);
  va_start(args, format);
  while (format[i] != '\0')
  {
    if (format[i] == '%' &&((format[i + 1] == 's') || (format[i + 1] == 'd') || (format[i + 1] == 'x')))
    {
      i++;
      if (format[i] == 's')
        count_len += ft_putstr(va_arg(args, char *));
      if (format[i] == 'd')
        count_len += ft_putnbr(va_arg(args, int));
      if (format[i] == 'x')
        count_len += ft_puthex(va_arg(args, unsigned int));
    }
    else
      count_len += ft_putchar(format[i]);
    i++;
  }
  va_end(args);
  return(count_len);
}
