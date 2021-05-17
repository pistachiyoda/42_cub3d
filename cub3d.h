#ifndef CUB3D_H
#define CUB3D_H
#include "./mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define texWidth 64
#define texHeight 64
#define mapWidth 10
#define mapHeight 10
#define width 640
#define height 480
typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	t_img	img;
	int		buf[height][width];
	double	zBuffer[width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
	t_sprite *sprites;
	int	cntSprites;
	int		*spriteOrder;
	double	*spriteDistance;
	int worldMap[mapWidth][mapHeight];
}				t_info;
int	main_loop(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
void	load_texture(t_info *info);
int cntSprites(t_info info);
t_sprite *setSprite(int cntSprites, t_info info);
void initSpriteOrder(t_info *info);
int			close_window(t_info *info);
#endif