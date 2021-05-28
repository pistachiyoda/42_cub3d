#include "cub3d.h"
#include <stdio.h>

void	initSpriteOrder(t_info *info)
{
	info->spriteOrder = (int *)malloc(info->cntSprites * sizeof(int));
	if (!info->spriteOrder)
		end_game(1, "malloc failed\n");
	info->spriteDistance = (double *)malloc(info->cntSprites * sizeof(double));
	if (!info->spriteDistance)
		end_game(1, "malloc failed\n");
}

typedef struct s_pair
{
	double	first;
	int		second;
}					t_pair;

void	key_update(t_info *info);

static int	compare(const void *first, const void *second)
{
	if (*(int *)first > *(int *)second)
		return (1);
	else if (*(int *)first < *(int *)second)
		return (-1);
	else
		return (0);
}

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

void	draw(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			info->img.data[y * (info->img.size_l / 4) + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	cast_floor(t_info *info)
{
	int		y;
	int		x;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		color;

	//FLOOR CASTING
	y = SCREEN_HEIGHT / 2 + 1;
	while (y < SCREEN_HEIGHT)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		rayDirX0 = info->dirX - info->planeX;
		rayDirY0 = info->dirY - info->planeY;
		rayDirX1 = info->dirX + info->planeX;
		rayDirY1 = info->dirY + info->planeY;
		// Current y position compared to the center of the screen (the horizon)
		p = y - SCREEN_HEIGHT / 2;
		// Vertical position of the camera.
		posZ = 0.5 * SCREEN_HEIGHT;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		rowDistance = posZ / p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		floorX = info->posX + rowDistance * rayDirX0;
		floorY = info->posY + rowDistance * rayDirY0;
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			cellX = (int)(floorX);
			cellY = (int)(floorY);
			// get the texture coordinate from the fractional part
			tx = (int)(TEX_WIDTH * (floorX - cellX)) & (TEX_WIDTH - 1);
			ty = (int)(TEX_HEIGHT * (floorY - cellY)) & (TEX_HEIGHT - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			// floor
			info->buf[y][x] = info->floor_color;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			color = info->ceiling_color;
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[SCREEN_HEIGHT - y - 1][x] = color;
			x++;
		}
		y++;
	}
}

void	cast_wall(t_info *info)
{
	int		y;
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit; //was there a wall hit?
	int		side; //was a NS or a EW wall hit?

	// WALL CASTING
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
		rayDirX = info->dirX + info->planeX * cameraX;
		rayDirY = info->dirY + info->planeY * cameraX;
		//which box of the map we're in
		mapX = (int)info->posX;
		mapY = (int)info->posY;
		//length of ray from one x or y-side to next x or y-side
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(info->worldMap[mapX][mapY] > 0 && info->worldMap[mapX][mapY] != 2) hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
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
		if (side == 0 && rayDirX > 0) texNum = 3;
		if (side == 0 && rayDirX <= 0) texNum = 0;
		if (side == 1 && rayDirY > 0) texNum = 2;
		if (side == 1 && rayDirY <= 0) texNum = 1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = info->posY + perpWallDist * rayDirY;
		else           wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)TEX_WIDTH);
		if(side == 0 && rayDirX > 0) texX = TEX_WIDTH - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TEX_WIDTH - texX - 1;
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
			info->buf[y][x] = color;
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		info->zBuffer[x] = perpWallDist; //perpendicular distance is used
		x++;
	}
}

void	cast_sprite(t_info *info)
{
	int		y;
	int		x;

	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < info->cntSprites; i++)
	{
		info->spriteOrder[i] = i;
		info->spriteDistance[i] = ((info->posX - info->sprites[i].x) * (info->posX - info->sprites[i].x) + (info->posY - info->sprites[i].y) * (info->posY - info->sprites[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(info->spriteOrder, info->spriteDistance, info->cntSprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < info->cntSprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = info->sprites[info->spriteOrder[i]].x - info->posX;
		double spriteY = info->sprites[info->spriteOrder[i]].y - info->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((SCREEN_WIDTH / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = (int)fabs((SCREEN_HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + SCREEN_HEIGHT / 2 + vMoveScreen;
		if(drawEndY >= SCREEN_HEIGHT) drawEndY = SCREEN_HEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = (int)fabs((SCREEN_HEIGHT / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= SCREEN_WIDTH) drawEndX = SCREEN_WIDTH - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < SCREEN_WIDTH && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
				int color = info->texture[4][TEX_WIDTH * texY + texX];
				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}

void	calc(t_info *info)
{
	cast_floor(info);
	cast_wall(info);
	cast_sprite(info);
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!info->worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!info->worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->key_s)
	{
		if (!info->worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!info->worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//move right if no wall behind you
	if (info->key_d)
	{
		if (!info->worldMap[(int)(info->posX + info->dirY * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirY * info->moveSpeed;
		if (!info->worldMap[(int)(info->posX)][(int)(info->posY - info->dirX * info->moveSpeed * -1)])
			info->posY += info->dirX * info->moveSpeed * -1;
	}
	//move left if no wall behind you
	if (info->key_a)
	{
		if (!info->worldMap[(int)(info->posX - info->dirY * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirY * info->moveSpeed;
		if (!info->worldMap[(int)(info->posX)][(int)(info->posY - info->dirX * info->moveSpeed * -1)])
			info->posY -= info->dirX * info->moveSpeed * -1;
	}
	//rotate to the right
	if (info->key_right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->key_left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (info->key_esc)
		exit(0);
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_AR_L)
		info->key_left = 1;
	else if (key == K_AR_R)
		info->key_right = 1;
	return (0);
}

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_AR_L)
		info->key_left = 0;
	else if (key == K_AR_R)
		info->key_right = 0;
	return (0);
}
