/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:42:18 by fmai              #+#    #+#             */
/*   Updated: 2021/05/28 17:47:28 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(
			info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(
			img->img, &img->bpp, &img->size_l, &img->endian);
	if (img->data == 0)
		end_game(1, "load image failed");
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
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
	t_img	img;

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
	load_image(info, info->texture[direction], parts[1], &img);
	free_parts(parts);
}
