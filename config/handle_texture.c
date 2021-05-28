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

void	file_exists(char *file_path)
{
	int	ret;

	ret = open(file_path, O_RDONLY);
	if (ret == -1)
		end_game(1, "file not exists\n");
	close(ret);
}

void	handle_texture(t_info *info, char *file_path, int direction)
{
	t_img	img;

	if (file_path == NULL)
		end_game(1, "invalid file path\n");
	file_exists(file_path);
	if (direction == 0)
		info->north_texture_path = file_path;
	if (direction == 1)
		info->west_texture_path = file_path;
	if (direction == 2)
		info->east_texture_path = file_path;
	if (direction == 3)
		info->south_texture_path = file_path;
	load_image(info, info->texture[direction], file_path, &img);
}
