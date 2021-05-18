/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:13:13 by fmai              #+#    #+#             */
/*   Updated: 2020/11/25 16:43:34 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *target;
	unsigned char *str;

	target = (unsigned char *)s1;
	str = (unsigned char *)s2;
	while (n)
	{
		if (*target != *str)
			return ((int)*target - (int)*str);
		target++;
		str++;
		n--;
	}
	return (0);
}
