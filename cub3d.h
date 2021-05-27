#ifndef CUB3D_H
#define CUB3D_H
#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
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
#define screenWidth 1000
#define screenHeight 700
# define SUCCESS 1
# define FAILED -1
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
	int		key_left;
	int		key_right;
	int		key_esc;
	t_img	img;
	int		buf[screenHeight][screenWidth];
	double	zBuffer[screenWidth];
	int		texture[5][4096];
	double	moveSpeed;
	double	rotSpeed;
	t_sprite *sprites;
	int	cntSprites;
	int		*spriteOrder;
	double	*spriteDistance;
	char	*north_texture_path;
	char	*east_texture_path;
	char	*west_texture_path;
	char	*south_texture_path;
	char	*sprite_texture_path;
	int		floor_color;
	int		ceiling_color;
	int 	**worldMap;
	int		map_height;
	int		map_width;
	char	initial_direction;
}				t_info;
int	main_loop(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int	load_texture(t_info *info);
void initSpriteOrder(t_info *info);
int			close_window(t_info *info);
int	read_config(t_info *info, char *file_path);
void init_position(t_info *info);
void end_game(int status, char *message);
#endif