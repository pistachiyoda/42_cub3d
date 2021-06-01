#include "cub3d.h"

void	set_floor_ceiling_color(t_info *info, int x, int y)
{
	int	color;

	info->buf[y][x] = info->floor_color;
	color = info->ceiling_color;
	color = (color >> 1) & 8355711;
	info->buf[SCREEN_HEIGHT - y - 1][x] = color;
}

float	calc_floor_step_x(t_info *info, double rowDistance)
{
	return (
		rowDistance * ((info->dirX + info->planeX)
			- (info->dirX - info->planeX)) / SCREEN_WIDTH);
}

float	calc_floor_step_y(t_info *info, double rowDistance)
{
	return (
		rowDistance * ((info->dirY + info->planeY)
			- (info->dirY - info->planeY)) / SCREEN_WIDTH);
}

void	cast_floor_line(t_info *info, int y, double rowDistance)
{
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		x;

	floorStepX = calc_floor_step_x(info, rowDistance);
	floorStepY = calc_floor_step_y(info, rowDistance);
	floorX = info->posX + rowDistance * (info->dirX - info->planeX);
	floorY = info->posY + rowDistance * (info->dirY - info->planeY);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		floorX += floorStepX;
		floorY += floorStepY;
		set_floor_ceiling_color(info, x, y);
		x++;
	}
}

void	cast_floor(t_info *info)
{
	int		y;
	float	rowDistance;

	y = SCREEN_HEIGHT / 2 + 1;
	while (y < SCREEN_HEIGHT)
	{
		rowDistance = (0.5 * SCREEN_HEIGHT) / (y - SCREEN_HEIGHT / 2);
		cast_floor_line(info, y, rowDistance);
		y++;
	}
}
