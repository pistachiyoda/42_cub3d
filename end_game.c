#include "cub3d.h"

void	free_info(t_info *info)
{
	int	i;

	mlx_destroy_window(info->mlx, info->win);
	i = 0;
	while (i < info->map_height)
	{
		free(info->worldMap[i]);
		i++;
	}
	free(info->worldMap);
}

int	close_window(t_info *info)
{
	free_info(info);
	ft_putstr_fd("End game.\n", 1);
	exit(0);
}

void	end_game_without_info(int status, char *message)
{
	ft_putstr_fd(message, 1);
	exit(status);
}

void	end_game(t_info *info, int status, char *message)
{
	free_info(info);
	ft_putstr_fd(message, 1);
	exit(status);
}
