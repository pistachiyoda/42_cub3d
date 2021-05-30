#include "cub3d.h"

void	key_update(t_info *info)
{
	key_move(info);
	key_rotate(info);
	if (info->key_esc)
		exit(0);
}
