#include "cub3d.h"

void	handle_key_w(t_info *info)
{
	if (!info->worldMap[(int)(
			info->posX + info->dirX * info->moveSpeed * 2)][(int)(info->posY)])
		info->posX += info->dirX * info->moveSpeed;
	if (!info->worldMap[(int)(
			info->posX)][(int)(info->posY + info->dirY * info->moveSpeed * 2)])
		info->posY += info->dirY * info->moveSpeed;
}

void	handle_key_s(t_info *info)
{
	if (!info->worldMap[(int)(
			info->posX - info->dirX * info->moveSpeed * 2)][(int)(info->posY)])
		info->posX -= info->dirX * info->moveSpeed;
	if (!info->worldMap[(int)(
			info->posX)][(int)(info->posY - info->dirY * info->moveSpeed * 2)])
		info->posY -= info->dirY * info->moveSpeed;
}

void	handle_key_d(t_info *info)
{
	if (!info->worldMap[(int)(
			info->posX + info->dirY * info->moveSpeed * 2)][(int)(info->posY)])
		info->posX += info->dirY * info->moveSpeed;
	if (!info->worldMap[(int)(
			info->posX)][(int)(info->posY - info->dirX * info->moveSpeed * 2)])
		info->posY += info->dirX * info->moveSpeed * -1;
}

void	handle_key_a(t_info *info)
{
	if (!info->worldMap[(int)(
			info->posX - info->dirY * info->moveSpeed * 2)][(int)(info->posY)])
		info->posX -= info->dirY * info->moveSpeed;
	if (!info->worldMap[(int)(
			info->posX)][(int)(info->posY - info->dirX * info->moveSpeed * -2)])
		info->posY -= info->dirX * info->moveSpeed * -1;
}

void	key_move(t_info *info)
{
	if (info->key_w)
		handle_key_w(info);
	if (info->key_s)
		handle_key_s(info);
	if (info->key_d)
		handle_key_d(info);
	if (info->key_a)
		handle_key_a(info);
}
