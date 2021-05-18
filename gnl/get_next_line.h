/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:55:45 by fmai              #+#    #+#             */
/*   Updated: 2021/05/19 01:57:07 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1000

int			make_line(char **save, int fd, char **line, int index);
int			make_save(char **save, int fd, int index);
int			handle_save(char **save, int fd, char **line);
int			handle_error(char *buf, char *save);
int			get_next_line(int fd, char **line);
size_t		ft_strlen_gnl(char *str);
char		*ft_strdup_gnl(char *src);
char		*ft_strnjoin(char *s1, char const *s2, int n);
int			newline_index(char *str);
#endif
