#include "cub3d.h"

void	cast_floor_ceiling(t_info *info)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT / 2 + 1;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			info->buf[y][x] = info->floor_color;
			info->buf[SCREEN_HEIGHT - y - 1][x] = info->ceiling_color;
			x++;
		}
		y++;
	}
}
