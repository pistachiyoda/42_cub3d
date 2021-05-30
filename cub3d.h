/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:37:37 by fmai              #+#    #+#             */
/*   Updated: 2021/05/30 13:58:17 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define	CUB3D_H
# include	"mlx.h"
# include	"libft.h"
# include	"get_next_line.h"
# include	"key_macos.h"
# include	<math.h>
# include	<fcntl.h>
# include	<stdlib.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# define	X_EVENT_KEY_PRESS	2
# define	X_EVENT_KEY_RELEASE	3
# define	X_EVENT_KEY_EXIT	17
# define	TEX_WIDTH			64
# define	TEX_HEIGHT			64
# define	SCREEN_WIDTH			1000
# define	SCREEN_HEIGHT		700
# define	SUCCESS				1
# define	FAILED				-1

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_sprite
{
	double		x;
	double		y;
}				t_sprite;

typedef struct s_info
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	void		*mlx;
	void		*win;
	int			key_a;
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	int			key_esc;
	t_img		img;
	int			buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	double		zBuffer[SCREEN_WIDTH];
	int			texture[5][4096];
	double		moveSpeed;
	double		rotSpeed;
	t_sprite	*sprites;
	int			cntSprites;
	int			*spriteOrder;
	double		*spriteDistance;
	char		*north_texture_path;
	char		*east_texture_path;
	char		*west_texture_path;
	char		*south_texture_path;
	char		*sprite_texture_path;
	int			floor_color;
	int			ceiling_color;
	int			**worldMap;
	int			map_height;
	int			map_width;
	char		initial_direction;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			stepX;
	int			stepY;
	int			hit;
	int			wall_x;
	int			side; //was a NS or a EW wall hit?
	int			texNum;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	double		perpWallDist;
	int			texX;
}				t_info;

typedef struct s_pair
{
	double	first;
	int		second;
}				t_pair;
int		main_loop(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int		load_texture(t_info *info);
void	initSpriteOrder(t_info *info);
int		close_window(t_info *info);
int		read_config(t_info *info, char *file_path);
void	init_position(t_info *info);
void	end_game(int status, char *message);
void	handle_texture(t_info *info, char *file_path, int direction);
void	handle_floor(t_info *info, char *color_text);
void	handle_ceiling(t_info *info, char *color_text);
int		handle_map(t_info *info, char *line, int *y);
void	check_map(t_info *info);
void	cast_floor(t_info *info);
void	cast_wall(t_info *info);
void	cast_sprite(t_info *info);
void	calc_sidedist(t_info *info);
void	calc_val_for_dda(t_info *info);
void	dda(t_info *info);
#endif