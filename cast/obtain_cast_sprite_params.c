#include "cub3d.h"

void	obtain_sprite_size(t_info *info, t_cast_stripe_params *params, int i)
{
	params->spriteX = info->sprites[info->spriteOrder[i]].x - info->posX;
	params->spriteY = info->sprites[info->spriteOrder[i]].y - info->posY;
	params->invDet = 1.0
		/ (info->planeX * info->dirY - info->dirX * info->planeY);
	params->transformX = params->invDet
		* (info->dirY * params->spriteX - info->dirX * params->spriteY);
	params->transformY = params->invDet
		* (-info->planeY * params->spriteX + info->planeX * params->spriteY);
	params->spriteScreenX = (int)((SCREEN_WIDTH / 2)
			* (1 + params->transformX / params->transformY));
	params->vMoveScreen = (int)(VMOVE / params->transformY);
	params->spriteHeight
		= (int)fabs((SCREEN_HEIGHT / params->transformY) / VDIV);
	params->spriteWidth
		= (int)fabs((SCREEN_HEIGHT / params->transformY) / UDIV);
}

void	obtain_cast_sprite_params(
	t_info *info, t_cast_stripe_params *params, int i)
{
	obtain_sprite_size(info, params, i);
	params->drawStartY = -params->spriteHeight / 2
		+ SCREEN_HEIGHT / 2 + params->vMoveScreen;
	if (params->drawStartY < 0)
		params->drawStartY = 0;
	params->drawEndY = params->spriteHeight / 2
		+ SCREEN_HEIGHT / 2 + params->vMoveScreen;
	if (params->drawEndY >= SCREEN_HEIGHT)
		params->drawEndY = SCREEN_HEIGHT - 1;
	params->drawStartX = -params->spriteWidth / 2 + params->spriteScreenX;
	if (params->drawStartX < 0)
		params->drawStartX = 0;
	params->drawEndX = params->spriteWidth / 2 + params->spriteScreenX;
	if (params->drawEndX >= SCREEN_WIDTH)
		params->drawEndX = SCREEN_WIDTH - 1;
	params->stripe = params->drawStartX;
}
