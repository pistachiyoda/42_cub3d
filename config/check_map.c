#include "cub3d.h"

void	check_cell(t_info *info, int x, int y)
{
	if (y > 0
		&& info->worldMap[y - 1][x] != 0
		&& info->worldMap[y - 1][x] != 1)
		end_game(info, 1, "Error:invalid map\n");
	if (y < (info->map_height - 1)
		&& info->worldMap[y + 1][x] != 0
		&& info->worldMap[y + 1][x] != 1)
		end_game(info, 1, "Error:invalid map\n");
	if (x > 0
		&& info->worldMap[y][x - 1] != 0
		&& info->worldMap[y][x - 1] != 1)
		end_game(info, 1, "Error:invalid map1\n");
	if (info->worldMap[y][x + 1] != 0
		&& info->worldMap[y][x + 1] != 1)
		end_game(info, 1, "Error:invalid map2\n");
	if ((y == 0
			|| x == 0
			|| y == info->map_height - 1)
		&& info->worldMap[y][x] == 0)
		end_game(info, 1, "Error:invalid map\n");
}

void	check_map(t_info *info)
{
	int	current_x;
	int	current_y;

	if (info->initial_direction == '\0')
		end_game(info, 1, "Error:invalid map\n");
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
			check_cell(info, current_x, current_y);
			current_x++;
		}
		current_y++;
	}
}
