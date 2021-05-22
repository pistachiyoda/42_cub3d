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
	printf("i = %d\n", i);
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

int	load_texture(t_info *info)
{
	t_img	img;

	if (!(info->texture = (int **)malloc(sizeof(int *) * 5)))
		return (FAILED);
	for (int i = 0; i < 5; i++)
	{
		if (!(info->texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (FAILED);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
			info->texture[i][j] = 0;
	}
	load_image(info, info->texture[0], "textures/kita.xpm", &img);
	load_image(info, info->texture[1], "textures/nishi.xpm", &img);
	load_image(info, info->texture[2], "textures/higashi.xpm", &img);
	load_image(info, info->texture[3], "textures/minami.xpm", &img);
	load_image(info, info->texture[4], "textures/colorstone.xpm", &img);
	return (SUCCESS);
}
// int handle_texture(t_info *info, char*line)
// {

// }

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

int handle_info(t_info *info, char *line)
{
	char **parts;
	int ret;

		printf("ccc\n");
		printf("line = %s\n", line);
	parts = ft_split(line, ' ');
	printf("parts[0] = %s\n", parts[0]);
	if (parts[0] == NULL)
	{
		printf("ddd\n");
		return 1;
	}
	if (ft_strcmp(parts[0], "R"))
	{
		printf("eee\n");
		return handle_resolution(info, line);
	}
	return 1;
}

int handle_map(t_info *info, char *line)
{
	return 1;
}

int info_completed(t_info *info)
{
	if (
		info->resolution_x != -1 &&
		info->resolution_y != -1 
		//&&
		// info->north_texture_path != NULL &&
		// info->east_texture_path != NULL &&
		// info->west_texture_path != NULL &&
		// info->south_texture_path != NULL &&
		// info->floor_color != -1 &&
		// info->ceiling_color != -1
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
	int		first_line;
	int		info_end;

	init_info(info);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return -1;

	ret = -1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (info_completed(info))
		{
			printf("aaa\n");
			handle_map(info, line);
			return 1;
		}
		else
		{
			printf("bbb\n");
			handle_info(info, line);
		}
	}
	return (1);
}