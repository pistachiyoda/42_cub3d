#include "cub3d.h"
#include <stdio.h>

void	check_color(char **color_text_parts)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (color_text_parts[i] == NULL)
			end_game(1, "invalid color text format\n");
		if (
			ft_atoi(color_text_parts[i]) < 0
			|| ft_atoi(color_text_parts[i]) > 255)
			end_game(1, "color out of range\n");
		j = 0;
		while (color_text_parts[i][j])
		{
			if (!ft_isdigit(color_text_parts[i][j]))
				end_game(1, "Error:Invalid color code");
			j++;
		}
		i++;
	}
	if (color_text_parts[3] != NULL)
		end_game(1, "Error:Too much color element.");
}

int	color_text_to_color_num(char *color_text)
{
	char	**color_text_parts;
	int		color_num;

	if (color_text == NULL)
		end_game(1, "color text is null\n");
	color_text_parts = ft_split(color_text, ',');
	check_color(color_text_parts);
	color_num = ft_atoi(color_text_parts[0]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[1]);
	color_num = (color_num << 8) + ft_atoi(color_text_parts[2]);
	free_parts(color_text_parts);
	return (color_num);
}

void	handle_floor(t_info *info, char **color_text)
{
	info->floor_color = color_text_to_color_num(color_text[1]);
	free_parts(color_text);
}

void	handle_ceiling(t_info *info, char **color_text)
{
	info->ceiling_color = color_text_to_color_num(color_text[1]);
	free_parts(color_text);
}
