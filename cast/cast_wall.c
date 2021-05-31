#include "cub3d.h"

void	calc_texnum(t_info *info, t_cast_wall_params *wall_params)
{	
	if (wall_params->side == 0 && wall_params->rayDirX <= 0)
		wall_params->texNum = 0;
	if (wall_params->side == 1 && wall_params->rayDirY <= 0)
		wall_params->texNum = 1;
	if (wall_params->side == 1 && wall_params->rayDirY > 0)
		wall_params->texNum = 2;
	if (wall_params->side == 0 && wall_params->rayDirX > 0)
		wall_params->texNum = 3;
}

void	calc_drawstart_end(t_cast_wall_params *wall_params)
{
	wall_params->drawStart = -wall_params->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (wall_params->drawStart < 0)
		wall_params->drawStart = 0;
	wall_params->drawEnd = wall_params->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (wall_params->drawEnd >= SCREEN_HEIGHT)
		wall_params->drawEnd = SCREEN_HEIGHT - 1;
}

void	calc_texX(t_info *info, t_cast_wall_params *wall_params)
{
	double	wallX;

	if (wall_params->side == 0)
		wallX = info->posY + wall_params->perpWallDist * wall_params->rayDirY;
	else
		wallX = info->posX + wall_params->perpWallDist * wall_params->rayDirX;
	wallX -= floor((wallX));
	wall_params->texX = (int)(wallX * (double)TEX_WIDTH);
	if (wall_params->side == 0 && wall_params->rayDirX > 0)
		wall_params->texX = TEX_WIDTH - wall_params->texX - 1;
	if (wall_params->side == 1 && wall_params->rayDirY < 0)
		wall_params->texX = TEX_WIDTH - wall_params->texX - 1;
}

void	set_colors(t_info *info, t_cast_wall_params *wall_params)
{
	double	step;
	double	texPos;
	int		texY;
	int		color;
	int		y;

	step = 1.0 * TEX_HEIGHT / wall_params->lineHeight;
	texPos = (wall_params->drawStart - SCREEN_HEIGHT / 2 + wall_params->lineHeight / 2)
		* step;
	y = wall_params->drawStart;
	while (y < wall_params->drawEnd)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		color = info->texture[wall_params->texNum][TEX_HEIGHT * texY + wall_params->texX];
		if (wall_params->side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][wall_params->wall_x] = color;
		y++;
	}
}

void	cast_wall(t_info *info)
{
	t_cast_wall_params wall_params;
	int	y;

	wall_params.wall_x = 0;
	while (wall_params.wall_x < SCREEN_WIDTH)
	{
		wall_params.hit = 0;
		calc_val_for_dda(info, &wall_params);
		dda(info, &wall_params);
		if (wall_params.side == 0)
			wall_params.perpWallDist = (
					wall_params.mapX - info->posX + (1 - wall_params.stepX) / 2)
				/ wall_params.rayDirX;
		else
			wall_params.perpWallDist = (
					wall_params.mapY - info->posY + (1 - wall_params.stepY) / 2)
				/ wall_params.rayDirY;
		wall_params.lineHeight = (int)(SCREEN_HEIGHT / wall_params.perpWallDist);
		calc_drawstart_end(&wall_params);
		calc_texnum(info, &wall_params);
		calc_texX(info, &wall_params);
		set_colors(info, &wall_params);
		info->zBuffer[wall_params.wall_x] = wall_params.perpWallDist;
		wall_params.wall_x++;
	}
}
