#include "cub3d.h"
#include <stdio.h>

void	draw(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			info->img.data[y * (info->img.size_l / 4) + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	cast_floor_ceiling(info);
	cast_wall(info);
	cast_sprite(info);
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_AR_L)
		info->key_left = 1;
	else if (key == K_AR_R)
		info->key_right = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_AR_L)
		info->key_left = 0;
	else if (key == K_AR_R)
		info->key_right = 0;
	return (0);
}
