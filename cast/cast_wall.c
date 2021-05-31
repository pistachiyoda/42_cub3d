#include "cub3d.h"

void	calc_texnum(t_info *info, t_cast_wall_params *params)
{	
	if (params->side == 0 && params->rayDirX <= 0)
		params->texNum = 0;
	if (params->side == 1 && params->rayDirY <= 0)
		params->texNum = 1;
	if (params->side == 1 && params->rayDirY > 0)
		params->texNum = 2;
	if (params->side == 0 && params->rayDirX > 0)
		params->texNum = 3;
}

void	calc_drawstart_end(t_cast_wall_params *params)
{
	params->drawStart = -params->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (params->drawStart < 0)
		params->drawStart = 0;
	params->drawEnd = params->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (params->drawEnd >= SCREEN_HEIGHT)
		params->drawEnd = SCREEN_HEIGHT - 1;
}

void	calc_texX(t_info *info, t_cast_wall_params *params)
{
	double	wallX;

	if (params->side == 0)
		wallX = info->posY + params->perpWallDist * params->rayDirY;
	else
		wallX = info->posX + params->perpWallDist * params->rayDirX;
	wallX -= floor((wallX));
	params->texX = (int)(wallX * (double)TEX_WIDTH);
	if (params->side == 0 && params->rayDirX > 0)
		params->texX = TEX_WIDTH - params->texX - 1;
	if (params->side == 1 && params->rayDirY < 0)
		params->texX = TEX_WIDTH - params->texX - 1;
}

void	set_colors(t_info *info, t_cast_wall_params *params)
{
	double	step;
	double	texPos;
	int		texY;
	int		color;
	int		y;

	step = 1.0 * TEX_HEIGHT / params->lineHeight;
	texPos = (params->drawStart - SCREEN_HEIGHT / 2 + params->lineHeight / 2)
		* step;
	y = params->drawStart;
	while (y < params->drawEnd)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		color = info->texture[params->texNum][TEX_HEIGHT * texY + params->texX];
		if (params->side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][params->wall_x] = color;
		y++;
	}
}

void	cast_wall(t_info *info)
{
	t_cast_wall_params	params;
	int					y;

	params.wall_x = 0;
	while (params.wall_x < SCREEN_WIDTH)
	{
		params.hit = 0;
		calc_val_for_dda(info, &params);
		dda(info, &params);
		if (params.side == 0)
			params.perpWallDist = (
					params.mapX - info->posX + (1 - params.stepX) / 2)
				/ params.rayDirX;
		else
			params.perpWallDist = (
					params.mapY - info->posY + (1 - params.stepY) / 2)
				/ params.rayDirY;
		params.lineHeight = (int)(SCREEN_HEIGHT / params.perpWallDist);
		calc_drawstart_end(&params);
		calc_texnum(info, &params);
		calc_texX(info, &params);
		set_colors(info, &params);
		info->zBuffer[params.wall_x] = params.perpWallDist;
		params.wall_x++;
	}
}
