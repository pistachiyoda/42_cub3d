#include "cub3d.h"
#include <stdio.h>

int			close_window(t_info *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(1);
	return(1);
}

int	main(void)
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
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,9,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{2,0,0,0,0,0,0,0,0,3},
											{4,4,4,4,4,4,4,4,4,4}
										};
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

	info.cntSprites = cntSprites(info);
	printf("info.cntSprite = %d\n", info.cntSprites);
	info.sprites = setSprite(info.cntSprites, info);
	initSpriteOrder(&info);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 11)))
		return (-1);
	for (int i = 0; i < 11; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}

	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, 17, 1L<<17, close_window, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
