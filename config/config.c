#include "cub3d.h"
#include "get_next_line.h"
#include <stdio.h>

int	ft_strcmp(char *a, char *b)
{
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

void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i] != NULL)
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

void	handle_info(t_info *info, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (parts[0] == NULL)
		return ;
	if (ft_strcmp(parts[0], "NO"))
		return (handle_texture(info, parts, 0));
	if (ft_strcmp(parts[0], "WE"))
		return (handle_texture(info, parts, 1));
	if (ft_strcmp(parts[0], "EA"))
		return (handle_texture(info, parts, 2));
	if (ft_strcmp(parts[0], "SO"))
		return (handle_texture(info, parts, 3));
	if (ft_strcmp(parts[0], "F"))
		return (handle_floor(info, parts));   //free
	if (ft_strcmp(parts[0], "C"))
		return (handle_ceiling(info, parts)); //free
	end_game(1, "invalid config key\n"); //free
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

int	read_config(t_info *info, char *file_path)
{
	int		fd;
	char	*line;
	int		ret;
	int		y;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		end_game(1, "file reading error\n");
	ret = -1;
	y = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (!info_completed(info))
			handle_info(info, line);
		else if (info->worldMap == NULL && ft_strcmp(line, ""))
		{
			free(line);
			continue ;
		}
		else if (info->worldMap != NULL && ft_strcmp(line, ""))
			end_game(1, "unexpected empty line\n");
		else if (info_completed(info))
			handle_map(info, line, &y);
		free(line);
	}
	check_map(info);
	init_position(info);
	return (1);
}
