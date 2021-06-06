#include "cub3d.h"
#include <stdio.h>

int	close_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(1);
	return (1);
}

void	end_game(int status, char *message)
{
	ft_putstr_fd(message, 1);
	exit(status);
}

void	init_map_info(t_info *info)
{
	info->cntSprites = 0;
	info->worldMap = NULL;
	info->map_height = 0;
	info->map_width = 0;
	info->north_texture_path = NULL;
	info->east_texture_path = NULL;
	info->west_texture_path = NULL;
	info->south_texture_path = NULL;
	info->floor_color = -1;
	info->ceiling_color = -1;
	info->initial_direction = '\0';
}

void	init_info(t_info *info)
{
	int	i;
	int	j;

	init_map_info(info);
	info->mlx = mlx_init();
	info->key_a = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_esc = 0;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		j = 0;
		while (j < SCREEN_WIDTH)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		end_game(1, "Error:invalid argument");
	init_info(&info);
	if (read_config(&info, argv[1]) != 1)
		exit(0);
	initSpriteOrder(&info);
	info.win = mlx_new_window(info.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "mlx");
	info.img.img = mlx_new_image(info.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(
			info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 1L << 17, close_window, &info);
	mlx_loop(info.mlx);
}
