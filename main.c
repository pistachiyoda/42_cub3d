#include "cub3d.h"
#include <stdio.h>

int			close_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(1);
	return(1);
}

int	main(int argc, char **argv)
{
	t_info info;
	info.mlx = mlx_init();

	info.posX = 5.0;
	info.posY = 5.5;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;
	info.key_a = 0;
	info.key_w = 0;
	info.key_s = 0;
	info.key_d = 0;
	info.key_esc = 0;

	int	worldMap[mapWidth][mapHeight] =
										{
											{1,1,1,1,1,1,1,1,1,1},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,5,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{4,4,4,4,4,4,4,4,4,4}
										};
	printf("argv[1] = %s\n", argv[1]);
	read_config(&info, argv[1]);
	int x = 0;
	while (x < mapWidth)
	{
		int y = 0;
		while (y < mapHeight)
		{
			info.worldMap[x][y] = worldMap[x][y];
			y++;
		}
		x++;
	}

	info.cntSprites = cntSprites(&info);
	printf("info.resolution_x = %d\n info.resolution_y = %d\n", info.resolution_x, info.resolution_y);
	info.sprites = setSprite(info.cntSprites, &info);
	initSpriteOrder(&info);

	for (int i = 0; i < info.resolution_y; i++)
	{
		for (int j = 0; j < info.resolution_x; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	// int screen_width;
	// int screen_height;
	// mlx_get_screen_size(info.mlx,&screen_width, &screen_height);
	
	info.win = mlx_new_window(info.mlx, info.resolution_x, info.resolution_y, "mlx");

	info.img.img = mlx_new_image(info.mlx, info.resolution_x, info.resolution_y);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 17, 1L<<17, close_window, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
