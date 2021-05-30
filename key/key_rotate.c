#include "cub3d.h"

void	rotate_right(t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = info->dirX;
	info->dirX = info->dirX * cos(-info->rotSpeed)
		- info->dirY * sin(-info->rotSpeed);
	info->dirY = oldDirX * sin(-info->rotSpeed)
		+ info->dirY * cos(-info->rotSpeed);
	oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(-info->rotSpeed)
		- info->planeY * sin(-info->rotSpeed);
	info->planeY = oldPlaneX * sin(-info->rotSpeed)
		+ info->planeY * cos(-info->rotSpeed);
}

void	rotate_left(t_info *info)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = info->dirX;
	info->dirX = info->dirX * cos(info->rotSpeed)
		- info->dirY * sin(info->rotSpeed);
	info->dirY = oldDirX * sin(info->rotSpeed)
		+ info->dirY * cos(info->rotSpeed);
	oldPlaneX = info->planeX;
	info->planeX = info->planeX * cos(info->rotSpeed)
		- info->planeY * sin(info->rotSpeed);
	info->planeY = oldPlaneX * sin(info->rotSpeed)
		+ info->planeY * cos(info->rotSpeed);
}

void	key_rotate(t_info *info)
{
	if (info->key_right)
		rotate_right(info);
	if (info->key_left)
		rotate_left(info);
}
