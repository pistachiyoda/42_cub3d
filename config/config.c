#include "cub3d.h"
#include "get_next_line.h"

int	ft_strcmp(char *a, char *b)
{
	while (1)
	{
		if (*a == '\0' && *b == '\0')
			return (1);
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
}

void	handle_info(t_info *info, char *line)
{
	char	**parts;

	parts = ft_split(line, ' ');
	if (parts[0] == NULL)
		return ;
	if (info->texture[0].data == NULL && ft_strcmp(parts[0], "NO"))
		return (handle_texture(info, parts, 0));
	if (info->texture[1].data == NULL && ft_strcmp(parts[0], "WE"))
		return (handle_texture(info, parts, 1));
	if (info->texture[2].data == NULL && ft_strcmp(parts[0], "EA"))
		return (handle_texture(info, parts, 2));
	if (info->texture[3].data == NULL && ft_strcmp(parts[0], "SO"))
		return (handle_texture(info, parts, 3));
	if (info->floor_color == -1 && ft_strcmp(parts[0], "F"))
		return (handle_floor(info, parts));
	if (info->ceiling_color == -1 && ft_strcmp(parts[0], "C"))
		return (handle_ceiling(info, parts));
	end_game(info, 1, "ERROR: Invalid config.\n");
}

int	info_completed(t_info *info)
{
	if (
		info->texture[0].data != NULL
		&& info->texture[1].data != NULL
		&& info->texture[2].data != NULL
		&& info->texture[3].data != NULL
		&& info->floor_color != -1
		&& info->ceiling_color != -1
	)
		return (1);
	return (0);
}

void	input_config(t_info *info, int fd)
{
	int		ret;
	int		y;
	char	*line;

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
			end_game(info, 1, "ERROR: Unexpected empty line.\n");
		else if (info_completed(info))
			handle_map(info, line, &y);
		free(line);
	}
}

void	read_config(t_info *info, char *file_path)
{
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		end_game(info, 1, "ERROR: Config file reading error.\n");
	input_config(info, fd);
	check_map(info);
	init_position(info);
}
