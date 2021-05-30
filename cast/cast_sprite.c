#include "cub3d.h"

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	set_sprite_pixel(t_info *info, t_cast_stripe_params *params)
{
	params->d = (params->y - params->vMoveScreen)
		* 256 - SCREEN_HEIGHT * 128 + params->spriteHeight * 128;
	params->texY = ((params->d * TEX_HEIGHT) / params->spriteHeight) / 256;
	params->color
		= info->texture[4][TEX_WIDTH * params->texY + params->texX];
	if ((params->color & 0x00FFFFFF) != 0)
		info->buf[params->y][params->stripe] = params->color;
	params->y++;
}

void	handle_sprite(t_info *info, int i)
{
	t_cast_stripe_params	params;

	obtain_cast_sprite_params(info, &params, i);
	while (params.stripe < params.drawEndX)
	{
		params.texX = (int)(
				(256 * (params.stripe
						- (-params.spriteWidth / 2 + params.spriteScreenX))
					* TEX_WIDTH / params.spriteWidth) / 256);
		if (params.transformY > 0 && params.stripe > 0
			&& params.stripe < SCREEN_WIDTH
			&& params.transformY < info->zBuffer[params.stripe])
			params.y = params.drawStartY;
		while (params.y < params.drawEndY)
		{
			set_sprite_pixel(info, &params);
		}
		params.stripe++;
	}
}

void	cast_sprite(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->cntSprites)
	{
		info->spriteOrder[i] = i;
		info->spriteDistance[i] = (
				(info->posX - info->sprites[i].x)
				* (info->posX - info->sprites[i].x)
				+ (info->posY - info->sprites[i].y)
				* (info->posY - info->sprites[i].y));
		i++;
	}
	sortSprites(info->spriteOrder, info->spriteDistance, info->cntSprites);
	i = 0;
	while (i < info->cntSprites)
	{
		handle_sprite(info, i);
		i++;
	}
}
