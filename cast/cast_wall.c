#include "cub3d.h"

void	calc_texnum(t_info *info)
{	
	if (info->side == 0 && info->rayDirX <= 0)
		info->texNum = 0;
	if (info->side == 1 && info->rayDirY <= 0)
		info->texNum = 1;
	if (info->side == 1 && info->rayDirY > 0)
		info->texNum = 2;
	if (info->side == 0 && info->rayDirX > 0)
		info->texNum = 3;
}

void	calc_drawstart_end(t_info *info)
{
	info->drawStart = -info->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (info->drawStart < 0)
		info->drawStart = 0;
	info->drawEnd = info->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (info->drawEnd >= SCREEN_HEIGHT)
		info->drawEnd = SCREEN_HEIGHT - 1;
}

void	calc_texX(t_info *info)
{
	double	wallX;

	if (info->side == 0)
		wallX = info->posY + info->perpWallDist * info->rayDirY;
	else
		wallX = info->posX + info->perpWallDist * info->rayDirX;
	wallX -= floor((wallX));
	info->texX = (int)(wallX * (double)TEX_WIDTH);
	if (info->side == 0 && info->rayDirX > 0)
		info->texX = TEX_WIDTH - info->texX - 1;
	if (info->side == 1 && info->rayDirY < 0)
		info->texX = TEX_WIDTH - info->texX - 1;
}

void	set_colors(t_info *info)
{
	double	step;
	double	texPos;
	int		texY;
	int		color;
	int		y;

	step = 1.0 * TEX_HEIGHT / info->lineHeight;
	texPos = (info->drawStart - SCREEN_HEIGHT / 2 + info->lineHeight / 2)
		* step;
	y = info->drawStart;
	while (y < info->drawEnd)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		color = info->texture[info->texNum][TEX_HEIGHT * texY + info->texX];
		if (info->side == 1)
			color = (color >> 1) & 8355711;
		info->buf[y][info->wall_x] = color;
		y++;
	}
}

void	cast_wall(t_info *info)
{
	int	y;

	info->wall_x = 0;
	while (info->wall_x < SCREEN_WIDTH)
	{
		info->hit = 0;
		calc_val_for_dda(info);
		dda(info);
		if (info->side == 0)
			info->perpWallDist = (
					info->mapX - info->posX + (1 - info->stepX) / 2)
				/ info->rayDirX;
		else
			info->perpWallDist = (
					info->mapY - info->posY + (1 - info->stepY) / 2)
				/ info->rayDirY;
		info->lineHeight = (int)(SCREEN_HEIGHT / info->perpWallDist);
		calc_drawstart_end(info);
		calc_texnum(info);
		calc_texX(info);
		set_colors(info);
		info->zBuffer[info->wall_x] = info->perpWallDist;
		info->wall_x++;
	}
}
