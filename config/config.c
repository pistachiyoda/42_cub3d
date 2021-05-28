#include "cub3d.h"
#include "get_next_line.h"
#include <stdio.h>

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (1)
	{
		if (*a == '\0' && *b == '\0')
		{
			return (1);
		}
		if (*a != *b)
		{
			return (0);
		}
		a++;
		b++;
	}
}

void	handle_info(t_info *info, char *line)
{
	char	**parts;
	int		ret;

	parts = ft_split(line, ' ');
	if (parts[0] == NULL)
		return ;
	if (ft_strcmp(parts[0], "NO"))
		return (handle_texture(info, parts[1], 0));
	if (ft_strcmp(parts[0], "WE"))
		return (handle_texture(info, parts[1], 1));
	if (ft_strcmp(parts[0], "EA"))
		return (handle_texture(info, parts[1], 2));
	if (ft_strcmp(parts[0], "SO"))
		return (handle_texture(info, parts[1], 3));
	if (ft_strcmp(parts[0], "S"))
		return (handle_texture(info, parts[1], 4));
	if (ft_strcmp(parts[0], "F"))
		return (handle_floor(info, parts[1]));
	if (ft_strcmp(parts[0], "C"))
		return (handle_ceiling(info, parts[1]));
	end_game(1, "invalid config key\n");
}

/**
 * 北
 */
void	n_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = -1.0;
	info->dirY = 0.0;
	info->planeX = 0.0;
	info->planeY = 0.66;
}

/**
 * 東
 */
void	e_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 0.0;
	info->dirY = 1.0;
	info->planeX = 0.66;
	info->planeY = 0.0;
}

/**
 * 西
 */
void	w_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 0.0;
	info->dirY = -1.0;
	info->planeX = -0.66;
	info->planeY = 0;
}

/**
 * 南
 */
void	s_position(t_info *info)
{
	info->posX = info->posX + 0.5;
	info->posY = info->posY + 0.5;
	info->dirX = 1.0;
	info->dirY = 0.0;
	info->planeX = 0;
	info->planeY = -0.66;
}

void	init_position(t_info *info)
{
	if (info->initial_direction == 'N')
		return (n_position(info));
	if (info->initial_direction == 'E')
		return (e_position(info));
	if (info->initial_direction == 'W')
		return (w_position(info));
	if (info->initial_direction == 'S')
		return (s_position(info));
}

int	info_completed(t_info *info)
{
	if (
		info->north_texture_path != NULL
		&& info->east_texture_path != NULL
		&& info->west_texture_path != NULL
		&& info->south_texture_path != NULL
		&& info->floor_color != -1
		&& info->ceiling_color != -1
	)
		return (1);
	return (0);
}

void	init_info(t_info *info)
{
	info->north_texture_path = NULL;
	info->east_texture_path = NULL;
	info->west_texture_path = NULL;
	info->south_texture_path = NULL;
	info->floor_color = -1;
	info->ceiling_color = -1;
	info->initial_direction = '\0';
}

void	check_map(t_info *info)
{
	int	current_x;
	int	current_y;

	if (info->initial_direction == '\0')
		end_game(1, "Error:invalid map\n");
	current_y = 0;
	while (current_y < info->map_height)
	{
		current_x = 0;
		while (info->worldMap[current_y][current_x] != -2)
		{
			if (info->worldMap[current_y][current_x] != 0)
			{
				current_x++;
				continue ;
			}
			if (current_y > 0
				&& info->worldMap[current_y - 1][current_x] != 0
				&& info->worldMap[current_y - 1][current_x] != 1)
				end_game(1, "Error:invalid map\n");
			if (current_y < (info->map_height - 1)
				&& info->worldMap[current_y + 1][current_x] != 0
				&& info->worldMap[current_y + 1][current_x] != 1)
				end_game(1, "Error:invalid map\n");
			if (current_x > 0
				&& info->worldMap[current_y][current_x - 1] != 0
				&& info->worldMap[current_y][current_x - 1] != 1)
				end_game(1, "Error:iinvalid map\n");
			if (info->worldMap[current_y][current_x + 1] != 0
				&& info->worldMap[current_y][current_x + 1] != 1)
				end_game(1, "Error:iinvalid map\n");
			if ((current_y == 0
					|| current_x == 0
					|| current_y == info->map_height - 1)
				&& info->worldMap[current_y][current_x] == 0)
				end_game(1, "Error:iinvalid map\n");
			current_x++;
		}
		current_y++;
	}
}

int	read_config(t_info *info, char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		info_end;
	int		map_width;
	int		map_height;
	int		y;

	init_info(info);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		end_game(1, "file reading error\n");
	ret = -1;
	y = 0;
	info->map_width = 0;
	info->map_height = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (!info_completed(info))
			handle_info(info, line);
		else if (info->worldMap == NULL && ft_strcmp(line, ""))
			continue ;
		else if (info->worldMap != NULL && ft_strcmp(line, ""))
			end_game(1, "unexpected empty line\n");
		else if (info_completed(info))
		{
			handle_map(info, line, &y);
		}
	}
	check_map(info);
	return (1);
}
