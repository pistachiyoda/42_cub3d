/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:55:37 by fmai              #+#    #+#             */
/*   Updated: 2021/05/30 22:45:59 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	cnt;

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

char	*ft_strdup_gnl(char *src)
{
	int		str_cnt;
	char	*malloc_p;
	int		i;

	str_cnt = ft_strlen_gnl(src);
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

char	*ft_strnjoin(char *s1, char const *s2, int n)
{
	size_t	len;
	char	*str;
	char	*ret;

	len = ft_strlen_gnl((char *)s1) + n + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	ret = str;
	while (*s1 != '\0')
		*str++ = *s1++;
	while (n--)
		*str++ = *s2++;
	*str = '\0';
	return (ret);
}

int	newline_index(char *str)
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

int	handle_error(char *buf, char *save)
{
	free(buf);
	free(save);
	return (-1);
}
