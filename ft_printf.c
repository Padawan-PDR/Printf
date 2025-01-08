/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrada <pedrada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:00:39 by pedrada           #+#    #+#             */
/*   Updated: 2025/01/08 18:12:06 by pedrada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit(long n, int base, int upper_case)
{
	int		count;
	char	*numbers;

	count = 0;
	if (upper_case == 0)
		numbers = "0123456789abcdef";
	else
		numbers = "0123456789ABCDEF";
	if (n < 0)
	{
		ft_putchar('-');
		return (print_digit(-n, base, upper_case) + 1);
	}
	else if (n < base)
		return (ft_putchar(numbers[n]));
	else
	{
		count = print_digit(n / base, base, upper_case);
		return (count + print_digit(n % base, base, upper_case));
	}
}

int	type_of_args(char type_indicator, va_list ap)
{
	int	count;

	count = 0;
	if (type_indicator == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (type_indicator == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (type_indicator == 'p')
	{
		count += ft_putstr("0x");
		count += print_digit((unsigned long) va_arg(ap, void *), 16, 0);
	}
	else if (type_indicator == 'd' || type_indicator == 'i')
		count += print_digit(va_arg(ap, int), 10, 0);
	else if (type_indicator == 'u')
		count += print_digit(va_arg(ap, unsigned int), 10, 0);
	else if (type_indicator == 'x')
		count += print_digit(va_arg(ap, unsigned int), 16, 0);
	else if (type_indicator == 'X')
		count += print_digit(va_arg(ap, unsigned int), 16, 1);
	else if (type_indicator == '%')
		count += ft_putchar('%');
	else
		count += write(1, &type_indicator, 1);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		n_elements;

	va_start(ap, s);
	n_elements = 0;
	while (*s)
	{
		if (*s == '%')
			n_elements += type_of_args(*(++s), ap);
		else
			n_elements += ft_putchar(*s);
		s++;
	}
	va_end(ap);
	return (n_elements);
}
