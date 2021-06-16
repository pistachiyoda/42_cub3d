#include "cub3d.h"

void	calc_tex(t_info *info, t_cast_wall_params *params)
{
	if (params->side == 0 && params->rayDirX <= 0)
		params->texture = info->texture[0];
	if (params->side == 1 && params->rayDirY <= 0)
		params->texture = info->texture[1];
	if (params->side == 1 && params->rayDirY > 0)
		params->texture = info->texture[2];
	if (params->side == 0 && params->rayDirX > 0)
		params->texture = info->texture[3];
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
	params->texX = (int)(wallX * (double)params->texture.img_width);
	if (params->side == 0 && params->rayDirX > 0)
		params->texX = params->texture.img_width - params->texX - 1;
	if (params->side == 1 && params->rayDirY < 0)
		params->texX = params->texture.img_width - params->texX - 1;
}

void	set_colors(t_info *info, t_cast_wall_params *params)
{
	double	step;
	double	texPos;
	int		texY;
	int		color;
	int		y;

	step = 1.0 * params->texture.img_height / params->lineHeight;
	texPos = (params->drawStart - SCREEN_HEIGHT / 2 + params->lineHeight / 2)
		* step;
	y = params->drawStart;
	while (y < params->drawEnd)
	{
		texY = (int)texPos & (params->texture.img_height - 1);
		texPos += step;
		color = params->texture.data[params->texture.img_height
			* texY + params->texX];
		info->buf[y][params->wall_x] = color;
		y++;
	}
}

void	cast_wall(t_info *info)
{
	t_cast_wall_params	params;

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
		calc_tex(info, &params);
		calc_texX(info, &params);
		set_colors(info, &params);
		info->zBuffer[params.wall_x] = params.perpWallDist;
		params.wall_x++;
	}
}
