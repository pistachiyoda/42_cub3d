/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:47:28 by fmai              #+#    #+#             */
/*   Updated: 2020/11/22 22:47:24 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	char			*ret;
	unsigned int	str_len;
	unsigned int	substr_len;

	if (s == NULL)
		return (NULL);
	str_len = (unsigned int)ft_strlen((char *)s);
	substr_len = str_len > (unsigned int)len ? (unsigned int)len : str_len;
	if (str_len < start)
		return (ft_strdup(""));
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (substr == NULL)
		return (NULL);
	ret = substr;
	s += start;
	while (substr_len--)
		*substr++ = *s++;
	*substr = '\0';
	return (ret);
}
