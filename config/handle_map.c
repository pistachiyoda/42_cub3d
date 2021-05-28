#include "cub3d.h"
#include <stdio.h>

int	proc_map_element(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == '2')
		return (2);
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (0);
	return (-1);
}

int	add_sprite(t_info *info, int y, int x)
{
	t_sprite	*new_sprites;
	int			i;

	new_sprites = (t_sprite *)malloc(sizeof(t_sprite) * (info->cntSprites + 1));
	if (!new_sprites)
		end_game(1, "malloc failed\n");
	i = 0;
	while (i < info->cntSprites)
	{
		new_sprites[i] = info->sprites[i];
		i++;
	}
	if (info->cntSprites != 0)
		free(info->sprites);
	info->sprites = new_sprites;
	info->sprites[i].y = (double)x + 0.5;
	info->sprites[i].x = (double)y + 0.5;
	info->cntSprites++;
	return (1);
}

void	handle_line(t_info *info, int y, char *line, int line_len)
{
	int	i;

	i = 0;
	info->worldMap[y] = (int *)malloc(sizeof(int) * (line_len + 1));
	if (!info->worldMap[y])
		end_game(1, "malloc failed\n");
	while (i < line_len)
	{
		if (!ft_strrchr(" 012NWES", line[i]))
			end_game(1, "Error:invalid map\n");
		info->worldMap[y][i] = proc_map_element(line[i]);
		if (info->worldMap[y][i] == 2)
			add_sprite(info, y, i);
		if (ft_strrchr("NWES", line[i]))
		{
			if (info->initial_direction != '\0')
				end_game(1, "Error:invalid map\n");
			info->posX = y;
			info->posY = i;
			info->initial_direction = line[i];
		}
		i++;
	}
	info->worldMap[y][i] = -2;
}

/**
 * worldMap仕様
 * 
 * 0 床
 * 1 壁
 * N, W, E, S プレイヤーの位置と方角
 * -1 左側パディング
 * -2 行の右端
 */
int	handle_map(t_info *info, char *line, int *y)
{
	int	**new_map_array;
	int	i;
	int	line_len;

	new_map_array = (int **)malloc(sizeof(int *) * ((*y) + 1));
	if (!new_map_array)
		end_game(1, "malloc failed\n");
	i = 0;
	while (i < *y)
	{
		new_map_array[i] = info->worldMap[i];
		i++;
	}
	if ((*y) != 0)
		free(info->worldMap);
	info->worldMap = new_map_array;
	line_len = ft_strlen(line);
	handle_line(info, *y, line, line_len);
	if (info->map_width < line_len)
		info->map_width = line_len;
	(info->map_height)++;
	(*y)++;
	return (1);
}
