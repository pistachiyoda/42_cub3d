/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 18:10:25 by fmai              #+#    #+#             */
/*   Updated: 2020/11/25 16:48:18 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		calc_digit(int n)
{
	int digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

static char		*if_int_minmax(void)
{
	char *str;

	str = (char *)malloc(sizeof(char) * 12);
	ft_memcpy(str, "-2147483648\0", 12);
	return (str);
}

char			*ft_itoa(int n)
{
	int		is_minus;
	int		digit;
	char	*ret;

	if (n == -2147483648)
		return (if_int_minmax());
	is_minus = n <= -1 ? 1 : 0;
	digit = calc_digit(n);
	ret = (char *)malloc(sizeof(char) * (digit + is_minus + 1));
	if (ret == NULL)
		return (NULL);
	if (is_minus)
	{
		n *= -1;
		*ret = '-';
	}
	ret += digit + is_minus;
	*ret = '\0';
	while (digit--)
	{
		ret--;
		*ret = n % 10 + '0';
		n /= 10;
	}
	return (is_minus ? ret - 1 : ret);
}
