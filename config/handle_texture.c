/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:42:18 by fmai              #+#    #+#             */
/*   Updated: 2021/06/18 16:23:22 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
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
		end_game(info, 1, "load image failed");
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

void	handle_texture(t_info *info, char **parts, int direction, char *line)
{
	if (!file_exists(parts[1]))
	{
		free(line);
		free_parts(parts);
		end_game(info, 1, "file not exists\n");
	}
	load_image(info, parts[1], direction);
	free_parts(parts);
}
