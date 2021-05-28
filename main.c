#include "cub3d.h"
#include <stdio.h>

int			close_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(1);
	return(1);
}

void	end_game(int status, char *message)
{
	ft_putstr_fd(message, 1);
	exit(status);
}

int	main(int argc, char **argv)
{
	t_info info;
	info.mlx = mlx_init();

	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;
	info.cntSprites = 0;
	info.worldMap = NULL;

	if (read_config(&info, argv[1]) != 1)
		exit(0);

	init_position(&info);
	initSpriteOrder(&info);
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "mlx");

	info.img.img = mlx_new_image(info.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 17, 1L<<17, close_window, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
