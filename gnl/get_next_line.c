/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:54:36 by fmai              #+#    #+#             */
/*   Updated: 2021/05/30 23:18:22 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_line(char **save, int fd, char **line, int index)
{
	int	i;

	i = 0;
	*line = (char *)malloc(sizeof(char) * (index + 1));
	if (!(*line))
		return (0);
	while (i < index)
	{
		(*line)[i] = save[fd][i];
		i++;
	}
	(*line)[i] = '\0';
	return (1);
}

int	make_save(char **save, int fd, int index)
{
	int		new_save_len;
	int		i;
	char	*tmp;

	new_save_len = ft_strlen_gnl(save[fd]) - index;
	tmp = (char *)malloc(sizeof(char) * new_save_len);
	if (!tmp)
		return (0);
	i = 0;
	while (i < new_save_len - 1)
	{
		tmp[i] = save[fd][index + i + 1];
		i++;
	}
	tmp[i] = '\0';
	free(save[fd]);
	save[fd] = tmp;
	return (1);
}

int	handle_save(char **save, int fd, char **line)
{
	int	i;

	if (!save[fd])
	{
		*line = ft_strdup_gnl("");
		if (!(*line))
			return (handle_error(NULL, NULL));
		return (0);
	}
	i = newline_index(save[fd]);
	if (i != -1)
	{
		if (!make_line(save, fd, line, i))
			return (handle_error(NULL, save[fd]));
		if (!make_save(save, fd, i))
			return (handle_error(NULL, save[fd]));
		return (1);
	}
	*line = ft_strdup_gnl(save[fd]);
	if (!(*line))
		return (handle_error(NULL, save[fd]));
	free(save[fd]);
	save[fd] = NULL;
	return (0);
}

int	get_next_line_loop(int fd, char *buf, char *save[256])
{
	int		buf_cnt;
	char	*tmp;

	buf_cnt = read(fd, buf, BUFFER_SIZE);
	if (!buf_cnt)
		return (1);
	if (buf_cnt == -1)
		return (handle_error(buf, save[fd]));
	if (!save[fd])
	{
		save[fd] = ft_strdup_gnl("");
		if (!save[fd])
			return (handle_error(buf, NULL));
	}
	tmp = ft_strnjoin(save[fd], buf, buf_cnt);
	if (!tmp)
		return (handle_error(buf, save[fd]));
	free(save[fd]);
	save[fd] = tmp;
	if (newline_index(save[fd]) != -1)
		return (1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*save[256];
	int			ret;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 256 || !buf)
		return (-1);
	while (1)
	{
		ret = get_next_line_loop(fd, buf, save);
		if (ret == 0)
			continue ;
		else if (ret == 1)
			break ;
		else
			return (ret);
	}
	free(buf);
	return (handle_save(save, fd, line));
}
