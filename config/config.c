#include "cub3d.h"
#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int ft_strcmp(char *a, char *b)
{
	int i;

	i = 0;
	while (1)
	{
		if (*a == '\0' && *b == '\0')
		{
			return 1;
		}
		if (*a != *b)
		{
			return 0;
		}
		a++;
		b++;
	}
}

int set_buf(t_info *info)
{
	int i;
	
	info->buf = (int **)ft_calloc(info->resolution_y, sizeof(int *));
	i = 0;
	while (i < info->resolution_y)
	{
		info->buf[i] = (int *)ft_calloc(info->resolution_x, sizeof(int));
		i++;
	}
	info->zBuffer = (double *)ft_calloc(info->resolution_x, sizeof(double));
	return (SUCCESS);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

int handle_texture(t_info *info, char*file_path, int direction)
{
	t_img	img;

	if (direction == 0)
		info->north_texture_path = file_path;
	if (direction == 1)
		info->west_texture_path = file_path;
	if (direction == 2)
		info->east_texture_path = file_path;
	if (direction == 3)
		info->south_texture_path = file_path;
	load_image(info, info->texture[direction], file_path, &img);
	return (SUCCESS);
}

int handle_resolution(t_info *info, char *line)
{
	char	**parts;
	int screen_x;
	int screen_y;
	int	config_x;
	int config_y;

	parts = ft_split(line, ' ');
	config_x = ft_atoi(parts[1]);
	config_y = ft_atoi(parts[2]);
	if (config_x <= 0 || config_y <= 0)
		return (FAILED);
	mlx_get_screen_size(info->mlx,&screen_x, &screen_y);
	info->resolution_x = screen_x < config_x ? screen_x : config_x;
	info->resolution_y = screen_y < config_y ? screen_y : config_y; 
	set_buf(info);
	return (SUCCESS);
}

int color_text_to_color_num(char *color_text)
{
	char **color_text_parts;
	int color_num;

	color_text_parts = ft_split(color_text, ',');

	color_num = ft_atoi(color_text_parts[0]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[1]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[2]);

	return (color_num);
}

int handle_floor(t_info *info, char *color_text)
{
	info->floor_color = color_text_to_color_num(color_text);
	return (SUCCESS);
}

int handle_ceiling(t_info *info, char *color_text)
{
	info->ceiling_color = color_text_to_color_num(color_text);
	return (SUCCESS);
}

int handle_info(t_info *info, char *line)
{
	char **parts;
	int ret;

	parts = ft_split(line, ' ');
	if (parts[0] == NULL)
	{
		return 1;
	}
	if (ft_strcmp(parts[0], "R"))
		return handle_resolution(info, line);
	if (ft_strcmp(parts[0], "NO"))
		return handle_texture(info, parts[1], 0);
	if (ft_strcmp(parts[0], "WE"))
		return handle_texture(info, parts[1], 1);
	if (ft_strcmp(parts[0], "EA"))
		return handle_texture(info, parts[1], 2);
	if (ft_strcmp(parts[0], "SO"))
		return handle_texture(info, parts[1], 3);
	if (ft_strcmp(parts[0], "S"))
		return handle_texture(info, parts[1], 4);
	if (ft_strcmp(parts[0], "F"))
		return handle_floor(info, parts[1]);
	if (ft_strcmp(parts[0], "C"))
		return handle_ceiling(info, parts[1]);
	return (SUCCESS);
}

int proc_map_element(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == '2')
		return (2);
	if (c == ' ')
		return (1);
	return (0);
}

int add_sprite(t_info *info, int y, int x)
{
	t_sprite *new_sprites;
	int i;

	new_sprites = (t_sprite *)malloc(sizeof(t_sprite) * (info->cntSprites + 1));
	i = 0;
	while (i < info->cntSprites)
	{
		new_sprites[i] = info->sprites[i];
		i++;
	}
	if (info->cntSprites != 0)
		free(info->sprites);
	info->sprites = new_sprites;
	info->sprites[i].x = (double)x + 0.5;
	info->sprites[i].y = (double)y + 0.5;
	info->cntSprites++;
	return (1);
}

//todo:0,1,2,N,S,E,W,space以外は弾くようなエラー処理
int handle_map(t_info *info, char *line, int *y)
{
	int **new_map_array;
	int i;
	int line_len;

	new_map_array = (int **)malloc(sizeof(int *) * ((*y) + 1));
	i = 0;
	while (i < *y)
	{
		new_map_array[i] = info->worldMap[i];
		i++;
	}
	if ((*y) != 0)
		free(info->worldMap);
	info->worldMap = new_map_array;

	i = 0;
	line_len = ft_strlen(line);
	info->worldMap[*y] = (int *)malloc(sizeof(int) * line_len);
	while (i < line_len)
	{
		info->worldMap[*y][i] = proc_map_element(line[i]);
		if (info->worldMap[*y][i] == 2)
			add_sprite(info, *y, i);
		i++;
	}	
	if (info->map_width < line_len)
		info->map_width = line_len;
	(info->map_height)++;
	(*y)++;
	return 1;
}

int info_completed(t_info *info)
{
	if (
		info->resolution_x != -1 &&
		info->resolution_y != -1 &&
		info->north_texture_path != NULL &&
		info->east_texture_path != NULL &&
		info->west_texture_path != NULL &&
		info->south_texture_path != NULL &&
		info->floor_color != -1 &&
		info->ceiling_color != -1
		)
		return 1;
	return 0;
}

void init_info(t_info *info)
{
	info->resolution_x = -1;
	info->resolution_y = -1;
	info->north_texture_path = NULL;
	info->east_texture_path = NULL;
	info->west_texture_path = NULL;
	info->south_texture_path = NULL;
	info->floor_color = -1;
	info->ceiling_color = -1;
}

int	read_config(t_info *info, char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		info_end;
	int 	map_width;
	int		map_height;

	init_info(info);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return -1;

	ret = -1;
	int y = 0;
	info->map_width = 0;
	info->map_height = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (info_completed(info) && ft_strcmp(line, ""))
			continue; // @todo mapがすでに埋まってたらエラーを出す
		else if (info_completed(info))
			handle_map(info, line, &y);
		else
			handle_info(info, line);
	}
	return (1);
}