/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:10:06 by zelkalai          #+#    #+#             */
/*   Updated: 2023/12/08 16:10:07 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	my_printf(const char *format, va_list ap)
{
	int	c;

	c = 0;
	if (*format == 'c')
		c += ft_putchar(va_arg(ap, int));
	else if (*format == 's')
		c += ft_putstr(va_arg(ap, char *));
	else if (*format == 'd')
		c += ft_putnbr(va_arg(ap, int));
	else if (*format == 'i')
		c += ft_putnbr(va_arg(ap, int));
	else if (*format == 'x')
		c += ft_putx(va_arg(ap, unsigned int), 16);
	else if (*format == 'X')
		c += ft_putx_uppercase(va_arg(ap, unsigned int), 16);
	else if (*format == 'p')
		c += ft_putpointer(va_arg(ap, unsigned long long));
	else if (*format == 'u')
		c += ft_putunsigned(va_arg(ap, unsigned int));
	else if (*format == '%')
		c += ft_putchar('%');
	return (c);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		c;

	c = 0;
	if (format == NULL)
		return (-1);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (-1);
			c += my_printf(format, ap);
		}
		else
			c += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (c);
}
