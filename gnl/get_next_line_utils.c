/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:55:37 by fmai              #+#    #+#             */
/*   Updated: 2021/05/18 20:06:52 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(char *str)
{
	size_t cnt;

	if (!str)
		return (0);
	cnt = 0;
	while (1)
	{
		if (*str == '\0')
			break ;
		str++;
		cnt++;
	}
	return (cnt);
}

char		*ft_strdup(char *src)
{
	int		str_cnt;
	char	*malloc_p;
	int		i;

	str_cnt = ft_strlen(src);
	malloc_p = (char *)malloc(sizeof(char) * str_cnt + 1);
	if (malloc_p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		malloc_p[i] = src[i];
		i++;
	}
	malloc_p[i] = '\0';
	return (malloc_p);
}

char		*ft_strnjoin(char *s1, char const *s2, int n)
{
	size_t	len;
	char	*str;
	char	*ret;

	len = ft_strlen((char *)s1) + n + 1;
	if ((str = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ret = str;
	while (*s1 != '\0')
		*str++ = *s1++;
	while (n--)
		*str++ = *s2++;
	*str = '\0';
	return (ret);
}

int			newline_index(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
