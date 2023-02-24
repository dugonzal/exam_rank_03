/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:41:22 by dugonzal          #+#    #+#             */
/*   Updated: 2023/02/24 16:57:13 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_putstr(char *str, int *i)
{
	if (!str)
		str = "(null)";
	while (*str)
		*i += write (1, str++, 1);
	return (*i);
}

int	nbr(long int n, int *a, int base)
{
	if (n < 0)
	{
		*a += write (1, "-", 1);
		n *= -1;
	}
	if (n >= base)
		nbr (n / base, a, base);
	*a += write (1, &"0123456789abcdef"[n % base], 1);
	return (*a);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;

	if (!str)
		return (-1);
	i = 0;
	va_start (ap, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			if (*str == 's')
				ft_putstr (va_arg (ap, char *), &i);
			else if (*str == 'd')
				nbr (va_arg(ap, int), &i, 10);
			else if (*str == 'x')
				nbr (va_arg(ap, unsigned int), &i, 16);
		}
		else
			i += (int) write (1, str, 1);
		str++;
	}
	va_end (ap);
	return (i);
}
