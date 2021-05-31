#include "cub3d.h"

void	calc_sidedist(t_info *info, t_cast_wall_params *params)
{
	if (params->rayDirX < 0)
	{
		params->stepX = -1;
		params->sideDistX = (info->posX - params->mapX) * params->deltaDistX;
	}
	else
	{
		params->stepX = 1;
		params->sideDistX
			= (params->mapX + 1.0 - info->posX) * params->deltaDistX;
	}
	if (params->rayDirY < 0)
	{
		params->stepY = -1;
		params->sideDistY = (info->posY - params->mapY) * params->deltaDistY;
	}
	else
	{
		params->stepY = 1;
		params->sideDistY
			= (params->mapY + 1.0 - info->posY) * params->deltaDistY;
	}
}

void	calc_val_for_dda(t_info *info, t_cast_wall_params *params)
{
	params->cameraX = 2 * params->wall_x / (double)SCREEN_WIDTH - 1;
	params->rayDirX = info->dirX + info->planeX * params->cameraX;
	params->rayDirY = info->dirY + info->planeY * params->cameraX;
	params->mapX = (int)info->posX;
	params->mapY = (int)info->posY;
	params->deltaDistX = fabs(1 / params->rayDirX);
	params->deltaDistY = fabs(1 / params->rayDirY);
	calc_sidedist(info, params);
}

void	dda(t_info *info, t_cast_wall_params *params)
{
	while (params->hit == 0)
	{
		if (params->sideDistX < params->sideDistY)
		{
			params->sideDistX += params->deltaDistX;
			params->mapX += params->stepX;
			params->side = 0;
		}
		else
		{
			params->sideDistY += params->deltaDistY;
			params->mapY += params->stepY;
			params->side = 1;
		}
		if (
			info->worldMap[params->mapX][params->mapY] > 0
			&& info->worldMap[params->mapX][params->mapY] != 2)
			params->hit = 1;
	}
}
