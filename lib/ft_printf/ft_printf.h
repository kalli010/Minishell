/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 20:29:47 by zelkalai          #+#    #+#             */
/*   Updated: 2023/12/12 20:29:51 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putunsigned(unsigned int n);
int	ft_putpointer(unsigned long long num);
int	ft_putx_uppercase(unsigned int d, unsigned int base);
int	ft_putx(unsigned int d, unsigned int base);
int	ft_putnbr(int num);
int	ft_printf(const char *format, ...);
int	ft_putstr(char *s);
int	ft_putchar(int c);
int	my_printf(const char *format, va_list ap);

#endif
