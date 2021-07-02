#include "cub3d.h"

void	free_info(t_info *info)
{
	int	i;

	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_image(info->mlx, info->texture[0].img);
	mlx_destroy_image(info->mlx, info->texture[1].img);
	mlx_destroy_image(info->mlx, info->texture[2].img);
	mlx_destroy_image(info->mlx, info->texture[3].img);
	mlx_destroy_image(info->mlx, info->img.img);
	i = 0;
	while (i < info->map_height)
	{
		free(info->worldMap[i]);
		i++;
	}
	free(info->worldMap);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	free(info);
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
