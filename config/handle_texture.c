/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:42:18 by fmai              #+#    #+#             */
/*   Updated: 2021/06/15 21:00:46 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	load_image(t_info *info, char *path, int direction)
{
	info->texture[direction].img = mlx_xpm_file_to_image(
			info->mlx, path,
			&info->texture[direction].img_width,
			&info->texture[direction].img_height);

	info->texture[direction].data = (int *)mlx_get_data_addr(
			info->texture[direction].img,
			&info->texture[direction].bpp,
			&info->texture[direction].size_l,
			&info->texture[direction].endian);
	if (info->texture[direction].data == 0)
		end_game(1, "load image failed");
}

int	file_exists(char *file_path)
{
	int	ret;

	ret = open(file_path, O_RDONLY);
	if (ret == -1)
		return (0);
	close(ret);
	return (1);
}

void	handle_texture(t_info *info, char **parts, int direction)
{
	if (parts[0] == NULL)
		end_game(1, "invalid file path\n");
	if (!file_exists(parts[1]))
	{
		free_parts(parts);
		end_game(1, "file not exists\n");
	}
	if (ft_strcmp(parts[0], "NO"))
		info->north_texture_path = parts[1];
	if (ft_strcmp(parts[0], "WE"))
		info->west_texture_path = parts[1];
	if (ft_strcmp(parts[0], "EA"))
		info->east_texture_path = parts[1];
	if (ft_strcmp(parts[0], "SO"))
		info->south_texture_path = parts[1];
	load_image(info, parts[1], direction);
	free_parts(parts);
}
