#include "cub3d.h"

void	calc_sidedist(t_info *info, t_cast_wall_params *wall_params)
{
	if (wall_params->rayDirX < 0)
	{
		wall_params->stepX = -1;
		wall_params->sideDistX = (info->posX - wall_params->mapX) * wall_params->deltaDistX;
	}
	else
	{
		wall_params->stepX = 1;
		wall_params->sideDistX = (wall_params->mapX + 1.0 - info->posX) * wall_params->deltaDistX;
	}
	if (wall_params->rayDirY < 0)
	{
		wall_params->stepY = -1;
		wall_params->sideDistY = (info->posY - wall_params->mapY) * wall_params->deltaDistY;
	}
	else
	{
		wall_params->stepY = 1;
		wall_params->sideDistY = (wall_params->mapY + 1.0 - info->posY) * wall_params->deltaDistY;
	}
}

void	calc_val_for_dda(t_info *info, t_cast_wall_params *wall_params)
{
	wall_params->cameraX = 2 * wall_params->wall_x / (double)SCREEN_WIDTH - 1;
	wall_params->rayDirX = info->dirX + info->planeX * wall_params->cameraX;
	wall_params->rayDirY = info->dirY + info->planeY * wall_params->cameraX;
	wall_params->mapX = (int)info->posX;
	wall_params->mapY = (int)info->posY;
	wall_params->deltaDistX = fabs(1 / wall_params->rayDirX);
	wall_params->deltaDistY = fabs(1 / wall_params->rayDirY);
	calc_sidedist(info, wall_params);
}

void	dda(t_info *info, t_cast_wall_params *wall_params)
{
	while (wall_params->hit == 0)
	{
		if (wall_params->sideDistX < wall_params->sideDistY)
		{
			wall_params->sideDistX += wall_params->deltaDistX;
			wall_params->mapX += wall_params->stepX;
			wall_params->side = 0;
		}
		else
		{
			wall_params->sideDistY += wall_params->deltaDistY;
			wall_params->mapY += wall_params->stepY;
			wall_params->side = 1;
		}
		if (
			info->worldMap[wall_params->mapX][wall_params->mapY] > 0
			&& info->worldMap[wall_params->mapX][wall_params->mapY] != 2)
			wall_params->hit = 1;
	}
}
