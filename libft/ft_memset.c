/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:27:36 by fmai              #+#    #+#             */
/*   Updated: 2020/11/22 04:02:09 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char *dst;

	dst = (unsigned char *)b;
	while (n)
	{
		*dst = (unsigned char)c;
		dst++;
		n--;
	}
	return (b);
}
