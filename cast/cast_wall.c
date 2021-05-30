#include "cub3d.h"

void calc_sidedist(t_info *info)
{
	if(info->rayDirX < 0)
	{
		info->stepX = -1;
		info->sideDistX = (info->posX - info->mapX) * info->deltaDistX;
	}
	else
	{
		info->stepX = 1;
		info->sideDistX = (info->mapX + 1.0 - info->posX) * info->deltaDistX;
	}
	if(info->rayDirY < 0)
	{
		info->stepY = -1;
		info->sideDistY = (info->posY - info->mapY) * info->deltaDistY;
	}
	else
	{
		info->stepY = 1;
		info->sideDistY = (info->mapY + 1.0 - info->posY) * info->deltaDistY;
	}
}

void calc_val_for_dda(t_info *info)
{
	info->cameraX = 2 * info->wall_x/ (double)SCREEN_WIDTH - 1;
	info->rayDirX = info->dirX + info->planeX * info->cameraX;
	info->rayDirY = info->dirY + info->planeY * info->cameraX;
	info->mapX = (int)info->posX;
	info->mapY = (int)info->posY;
	info->deltaDistX = fabs(1 / info->rayDirX);
	info->deltaDistY = fabs(1 / info->rayDirY);
	calc_sidedist(info);
}

void	cast_wall(t_info *info)
{
	int		y;
	double	perpWallDist;
	int		side; //was a NS or a EW wall hit?

	// WALL CASTING
	info->wall_x = 0;
	while (info->wall_x < SCREEN_WIDTH)
	{
		info->hit = 0;
		calc_val_for_dda(info);

		//perform DDA
		while (info->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(info->sideDistX < info->sideDistY)
			{
				info->sideDistX += info->deltaDistX;
				info->mapX += info->stepX;
				side = 0;
			}
			else
			{
				info->sideDistY += info->deltaDistY;
				info->mapY += info->stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(info->worldMap[info->mapX][info->mapY] > 0 && info->worldMap[info->mapX][info->mapY] != 2) info->hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (info->mapX - info->posX + (1 - info->stepX) / 2) / info->rayDirX;
		else          perpWallDist = (info->mapY - info->posY + (1 - info->stepY) / 2) / info->rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
		//texturing calculations
		//int texNum = info->worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		int texNum;
		if (side == 0 && info->rayDirX > 0) texNum = 3;
		if (side == 0 && info->rayDirX <= 0) texNum = 0;
		if (side == 1 && info->rayDirY > 0) texNum = 2;
		if (side == 1 && info->rayDirY <= 0) texNum = 1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = info->posY + perpWallDist * info->rayDirY;
		else           wallX = info->posX + perpWallDist * info->rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)TEX_WIDTH);
		if(side == 0 && info->rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(side == 1 && info->rayDirY < 0) texX = TEX_WIDTH - texX - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEX_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
			int texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step;
			int color = info->texture[texNum][TEX_HEIGHT * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			info->buf[y][info->wall_x] = color;
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[info->wall_x] = perpWallDist; //perpendicular distance is used
		info->wall_x++;
	}
}