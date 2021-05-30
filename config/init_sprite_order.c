#include "cub3d.h"

void	initSpriteOrder(t_info *info)
{
	info->spriteOrder = (int *)malloc(info->cntSprites * sizeof(int));
	if (!info->spriteOrder)
		end_game(1, "malloc failed\n");
	info->spriteDistance = (double *)malloc(info->cntSprites * sizeof(double));
	if (!info->spriteDistance)
		end_game(1, "malloc failed\n");
}
