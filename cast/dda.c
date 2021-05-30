#include "cub3d.h"

void	calc_sidedist(t_info *info)
{
	if (info->rayDirX < 0)
	{
		info->stepX = -1;
		info->sideDistX = (info->posX - info->mapX) * info->deltaDistX;
	}
	else
	{
		info->stepX = 1;
		info->sideDistX = (info->mapX + 1.0 - info->posX) * info->deltaDistX;
	}
	if (info->rayDirY < 0)
	{
		info->stepY = -1;
		info->sideDistY = (info->posY - info->mapY) * info->deltaDistY;
	}
	else
	{
		info->stepY = 1;
		info->sideDistY = (info->mapY + 1.0 - info->posY) * info->deltaDistY;
	}
}

void	calc_val_for_dda(t_info *info)
{
	info->cameraX = 2 * info->wall_x / (double)SCREEN_WIDTH - 1;
	info->rayDirX = info->dirX + info->planeX * info->cameraX;
	info->rayDirY = info->dirY + info->planeY * info->cameraX;
	info->mapX = (int)info->posX;
	info->mapY = (int)info->posY;
	info->deltaDistX = fabs(1 / info->rayDirX);
	info->deltaDistY = fabs(1 / info->rayDirY);
	calc_sidedist(info);
}

void	dda(t_info *info)
{
	while (info->hit == 0)
	{
		if (info->sideDistX < info->sideDistY)
		{
			info->sideDistX += info->deltaDistX;
			info->mapX += info->stepX;
			info->side = 0;
		}
		else
		{
			info->sideDistY += info->deltaDistY;
			info->mapY += info->stepY;
			info->side = 1;
		}
		if (
			info->worldMap[info->mapX][info->mapY] > 0
			&& info->worldMap[info->mapX][info->mapY] != 2)
			info->hit = 1;
	}
}
