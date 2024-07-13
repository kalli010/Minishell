/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:08:52 by zelkalai          #+#    #+#             */
/*   Updated: 2023/12/12 17:08:54 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int num)
{
	long int	number;
	int			c;

	c = 0;
	number = num;
	if (number < 0)
	{
		ft_putchar('-');
		number *= -1;
		c++;
	}
	if (number > 9)
		c += ft_putnbr(number / 10);
	c += ft_putchar(number % 10 + 48);
	return (c);
}

int	ft_putx(unsigned int d, unsigned int base)
{
	int		c;
	char	*s;

	s = "0123456789abcdef";
	c = 0;
	if (d < base)
		c += ft_putchar(s[d]);
	else
	{
		c += ft_putx(d / base, base);
		c += ft_putchar(s[d % base]);
	}
	return (c);
}

int	ft_putx_uppercase(unsigned int d, unsigned int base)
{
	int		c;
	char	*s;

	s = "0123456789ABCDEF";
	c = 0;
	if (d < base)
		return (ft_putchar(s[d]));
	else
	{
		c = ft_putx_uppercase(d / base, base);
		return (c + ft_putchar(s[d % base]));
	}
}

int	ft_putpointer(unsigned long long num)
{
	char	hex_string[16];
	char	*hex_digits;
	int		index;
	int		count;
	int		i;

	if (num == 0)
		return (ft_putstr("(nil)"));
	hex_digits = "0123456789abcdef";
	index = 15;
	count = 0;
	hex_string[index--] = '\0';
	while (num > 0)
	{
		hex_string[index--] = hex_digits[num % 16];
		num /= 16;
	}
	count += ft_putchar('0') + ft_putchar('x');
	i = index + 1;
	while (hex_string[i] != '\0')
	{
		count += ft_putchar(hex_string[i]);
		i++;
	}
	return (count);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n / 10 != 0)
	{
		count += ft_putunsigned(n / 10);
	}
	count += ft_putchar(n % 10 + '0');
	return (count);
}
