#include "cub3d.h"

/**
 * 北
 */
void	n_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
}

/**
 * 東
 */
void	e_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 0.0;
	info->dirY = 1.0;
	info->planeX = 0.66;
	info->planeY = 0.0;
}

/**
 * 西
 */
void	w_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 0.0;
	info->dirY = -1.0;
	info->planeX = -0.66;
	info->planeY = 0;
}

/**
 * 南
 */
void	s_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 1.0;
	info->dirY = 0.0;
	info->planeX = 0;
	info->planeY = -0.66;
}

void	init_position(t_info *info)
{
	if (info->initial_direction == 'N')
		return (n_position(info));
	if (info->initial_direction == 'E')
		return (e_position(info));
	if (info->initial_direction == 'W')
		return (w_position(info));
	if (info->initial_direction == 'S')
		return (s_position(info));
}
